#include "file.h"


int our_get_buffer(AVCodecContext *pCodecCtx, AVFrame *frame) 
{
    int ret = avcodec_default_get_buffer(pCodecCtx, frame);
    uint64_t *pts = av_malloc(sizeof(uint64_t));
    *pts = global_video_pkt_pts;
    frame->opaque = pts;
    return ret;
}

void our_release_buffer(AVCodecContext *pCodecCtx, AVFrame *frame)
{
    if(frame)
	av_freep(&frame->opaque);
    avcodec_default_release_buffer(pCodecCtx, frame);
}


int get_file_info(File *file)
{
    if(av_open_input_file(&file->pFormatCtx, file->name, NULL, 0, NULL) != 0)
    {
	fprintf(stderr, "fail to open file : av_open_input_file\n");
	return -1;
    }
    if(av_find_stream_info(file->pFormatCtx) < 0)
    {
	fprintf(stderr, "fail to read stream : av_open_input_file\n");
	return -1;
    }

    dump_format(file->pFormatCtx, 0, file->name, 0);
    return 0;
}


void find_av_streams(File *file, Media *video, Media *audio) {
    int i;
    video->track = -1;
    audio->track = -1;
    for (i = 0; i < file->pFormatCtx->nb_streams; i++)
    {
	if(file->pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
	    video->track = i;
	    video->stream = file->pFormatCtx->streams[i];
	    video->pCodecCtx = file->pFormatCtx->streams[i]->codec;
	}
	if(file->pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
	    audio->track = i;
	    audio->stream = file->pFormatCtx->streams[i];
	    audio->pCodecCtx = file->pFormatCtx->streams[i]->codec;
	    find_audio_decoder(audio);
	}
    }
}

int find_decoder(Media *media)
{
    //find decoder for the video stream
    media->pCodec = avcodec_find_decoder(media->pCodecCtx->codec_id);
    if(media->pCodec == NULL)
    {
	fprintf(stderr, "fail to find codec : find_decoder\n");
	return -1;
    }
    if(avcodec_open(media->pCodecCtx, media->pCodec) < 0)
    {
	fprintf(stderr, "fail to open codec : find_decoder\n");
	return -1;
    }

    switch(media->mediaType) {
    case VIDEO:
	media->pCodecCtx->get_buffer = our_get_buffer;
	media->pCodecCtx->release_buffer = our_release_buffer;
	break;

    case AUDIO:
	media->audio_buf_size = 0;
	media->audio_buf_index = 0;
	memset(&media->audio_pkt, 0, sizeof(media->audio_pkt));
	SDL_PauseAudio(0);
	break;
    default:
	fprintf(stderr, "unknown media type : find_decoder\n");
	return -1;
    }
    
    return 0;
}

int queue_av_pkt(void *arg) {
    AVPacket *pkt = av_mallocz(sizeof(AVPacket));
    State *state = (State *)arg;
    init_queue(&state->audio->rawDataBuf);
    init_queue(&state->video->rawDataBuf);
    while(true) {
	//if queue is full, wait for eat
	if(state->video->rawDataBuf.size > MAX_VIDEO_QUEUE_SIZE || state->audio->rawDataBuf.size > MAX_AUDIO_QUEUE_SIZE) {
	    SDL_Delay(10);
//	    fprintf(stderr, "queue is full, waiting for decoding : queue_av_pkt\n");
	    continue;
	}
	//if packet is valid
	if(av_read_frame(state->file->pFormatCtx, pkt) < 0) {
	    if(url_ferror(state->file->pFormatCtx->pb) == 0) {
		SDL_Delay(100);
		continue;
	    }else {
		fprintf(stderr, "read frame error, maybe come to end of file : queue_av_pkt\n");
		break;		// error or end of file
	    }
	}
	//put packet into AV queue
	if(pkt->stream_index == state->video->track) {
	    add_to_queue(&state->video->rawDataBuf, pkt);
	}else if(pkt->stream_index == state->audio->track) {
	    add_to_queue(&state->audio->rawDataBuf, pkt);
	}else {
	    fprintf(stderr, "neither audio or video track : queue_av_pkt\n");
	    av_free_packet(pkt);
	}
    }
    return 0;
}

