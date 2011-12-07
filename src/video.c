#include "video.h"
#include "display.h"
#include "sync.h"

int decode_video(void *arg)
{
    LOGI("created decode thread");
    Media *video = (Media *)arg;
    AVFrame *pFrame;
    int frameFinished;
    double pts;
    AVPacket packet;
    AVPacket *pkt = &packet;
    pFrame = avcodec_alloc_frame();
    while(true) {
	if(get_from_queue(&video->raw_data_buf, pkt) < 0) {
	    LOGE("%s", "fail to get video pkt from queue : decode_video");
	    break;
	}
	if(pkt->data == flush_pkt.data) {
	    avcodec_flush_buffers(video->stream->codec);
	    continue;
	}
	pts = 0;
	global_video_pkt_pts = pkt->pts;
	avcodec_decode_video2(video->codec_ctx, pFrame, &frameFinished, &packet);
	if(pkt->dts != AV_NOPTS_VALUE && pFrame->opaque && *(uint64_t *)pFrame->opaque != AV_NOPTS_VALUE) {
	    pts = *(uint64_t *)pFrame->opaque;
	} else if(pkt->dts != AV_NOPTS_VALUE) {
	    pts = pkt->dts;	    
	}
	else {
	    pts = 0;
	}
	pts *= av_q2d(video->stream->time_base);
	//did we get a video frame?
	if(frameFinished) {
	    pts = sync_video(video, pFrame, pts);
	    if(video_frame_convert(video, pFrame, pts) < 0)
		break;
	}
    }
    av_free_packet(pkt);
    av_free(pFrame);
    return 0;
}


int video_frame_convert(Media *video, AVFrame *pFrame, double pts)
{
    AVPicture pict;
    int dstPixFmt;
    static struct SwsContext *imgConvertCtx;
    VideoFrame *vf;

    SDL_LockMutex(video->frame_buf_mutex);
    while(video->frame_buf_size >= VIDEO_FRAME_QUEUE_SIZE) {
	SDL_CondWait(video->frame_buf_cond, video->frame_buf_mutex);
    }
    SDL_UnlockMutex(video->frame_buf_mutex);

    vf = &video->frame_buf[video->frame_index];
    if(vf->bmp) {
	SDL_LockYUVOverlay(vf->bmp);
	dstPixFmt = PIX_FMT_YUV420P;
	pict.data[0] = vf->bmp->pixels[0];
	pict.data[1] = vf->bmp->pixels[2];
	pict.data[2] = vf->bmp->pixels[1];

	pict.linesize[0] = vf->bmp->pitches[0];
	pict.linesize[1] = vf->bmp->pitches[2];
	pict.linesize[2] = vf->bmp->pitches[1];

	if(imgConvertCtx == NULL) {
	    int w = video->stream->codec->width;
	    int h = video->stream->codec->height;
	    imgConvertCtx = sws_getContext(w, h, video->stream->codec->pix_fmt, w, h, dstPixFmt, SWS_BICUBIC, NULL, NULL, NULL);
	    if(imgConvertCtx == NULL) {
		LOGE("fail to init the conversion context : video_frame_queue");
		exit(-1);
	    }
	}
	sws_scale(imgConvertCtx, pFrame->data, pFrame->linesize, 0, video->stream->codec->height, pict.data, pict.linesize);
	SDL_UnlockYUVOverlay(vf->bmp);
	vf->pts = pts;

	SDL_LockMutex(video->frame_buf_mutex);
	video->frame_buf_size++;
	SDL_UnlockMutex(video->frame_buf_mutex);
    }
    return 0;
}


int our_get_buffer(AVCodecContext *codec_ctx, AVFrame *frame)
{
    int ret = avcodec_default_get_buffer(codec_ctx, frame);
    uint64_t *pts = av_malloc(sizeof(uint64_t));
    *pts = global_video_pkt_pts;
    frame->opaque = pts;
    return ret;
}

void our_release_buffer(AVCodecContext *codec_ctx, AVFrame *frame)
{
    if(frame)
	av_freep(&frame->opaque);
    avcodec_default_release_buffer(codec_ctx, frame);
}


void init_video(Media *video)
{
    memset(video, 0, sizeof(Media));
    global_video_pkt_pts = AV_NOPTS_VALUE;
    video->media_type = VIDEO;
    video->frame_timer = (double)av_gettime() / 1000000.0;
    video->frame_last_delay = 40e-3;
    video->find_stream = find_av_streams;
    video->find_codec = find_decoder;
    video->frame_buf_mutex = SDL_CreateMutex();
    video->frame_buf_cond = SDL_CreateCond();
    video->play_cond = SDL_CreateCond();    
    video->play_mutex = SDL_CreateMutex();    
    video->frame_last_delay = 40e-3;
    video->video_current_pts_time = av_gettime();
    video->frame_timer = (double)av_gettime() / 1000000.0;
    video->play = play_video;
    video->get_info = get_av_info;
}

