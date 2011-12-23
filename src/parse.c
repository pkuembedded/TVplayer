#include "parse.h"
#include "video.h"

int get_content_info(Content *content)
{
    if(av_open_input_file(&content->format_ctx, content->name, NULL, 0, NULL) != 0)
    {
	return -1;
    }
    if(av_find_stream_info(content->format_ctx) < 0)
    {
	return -1;
    }

    av_dump_format(content->format_ctx, 0, content->name, 0);
    return 0;
}


void find_av_streams(Content *content, Media *video, Media *audio) {
    int i;
    video->track = -1;
    audio->track = -1;
    for (i = 0; i < content->format_ctx->nb_streams; i++)
    {
	if(content->format_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
	    video->track = i;
	    video->stream = content->format_ctx->streams[i];
	    video->codec_ctx = content->format_ctx->streams[i]->codec;
	}
	if(content->format_ctx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
	    audio->track = i;
	    audio->stream = content->format_ctx->streams[i];
	    audio->codec_ctx = content->format_ctx->streams[i]->codec;
	    find_audio_decoder(audio);
	}
    }
}

int find_decoder(Media *media)
{
    //find decoder for the video stream
    media->codec = avcodec_find_decoder(media->codec_ctx->codec_id);
    if(media->codec == NULL)
    {
	LOGE("fail to find codec : find_decoder");
	return -1;
    }
    if(avcodec_open(media->codec_ctx, media->codec) < 0)
    {
	LOGE("fail to open codec : find_decoder");
	return -1;
    }

    switch(media->media_type) {

    case VIDEO:
	media->codec_ctx->get_buffer = our_get_buffer;
	media->codec_ctx->release_buffer = our_release_buffer;
	break;

    case AUDIO:
	media->audio_buf_size = 0;
	media->audio_buf_index = 0;
	memset(&media->audio_pkt, 0, sizeof(media->audio_pkt));
	SDL_PauseAudio(0);
	break;

    default:
	LOGV("unknown media type : find_decoder");
	return -1;
    }
    
    return 0;
}

int queue_av_pkt(void *arg) {
    LOGI("created reading thread");
    AVPacket *pkt = av_mallocz(sizeof(AVPacket));
    State *state = (State *)arg;
    init_queue(&state->audio->raw_data_buf);
    init_queue(&state->video->raw_data_buf);
    while(true) {
	if(state->video->raw_data_buf.size > MAX_VIDEO_QUEUE_SIZE || state->audio->raw_data_buf.size > MAX_AUDIO_QUEUE_SIZE) {
	    SDL_Delay(10);
//	    LOGW("queue is full, waiting for decoding");
	    continue;
	}
	if(av_read_frame(state->content->format_ctx, pkt) < 0) {
	    if(url_ferror(state->content->format_ctx->pb) == 0) {
		SDL_Delay(100);
		continue;
	    }else {
		LOGW("read frame error, maybe come to end of content : queue_av_pkt");
		break;		// error or end of content
	    }
	}
	//put packet into AV queue
	if(pkt->stream_index == state->video->track) {
	    add_to_queue(&state->video->raw_data_buf, pkt);
	}else if(pkt->stream_index == state->audio->track) {
	    add_to_queue(&state->audio->raw_data_buf, pkt);
	}else {
	    LOGV("neither audio or video track : queue_av_pkt");
	    av_free_packet(pkt);
	}
    }
    return 0;
}

void get_av_info(void *arg) {
    Media *media = (Media *)arg;
    int is_output = false; //make msg short
    avcodec_string(media->info, sizeof(media->info), media->codec_ctx, is_output);
    LOGI("%s", media->info);
}
