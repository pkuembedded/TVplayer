#include "video.h"
#include "display.h"
#include "sync.h"

//void *convert_frame(void *arg) {
//    OneFrame *frame_to_convert = (OneFrame *)arg;
//    if(video_frame_convert(frame_to_convert->video, frame_to_convert->pFrame, frame_to_convert->pts) < 0) {
//	LOGE("video_frame_convert error!");
//    }
//}

void decode_video(void *arg)
{
    LOGI("created decode thread");
    Media *video = (Media *)arg;
    AVFrame *pFrame;
    double pts;
    int frameFinished;
    int decode_len;
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
	    LOGW("flush buffers");
	    continue;
	}
	global_video_pkt_pts = pkt->pts;
	if((decode_len = avcodec_decode_video2(video->codec_ctx, pFrame, &frameFinished, &packet)) < 0) {
	    LOGE("error in decode video");
	    break;
	}

	if(pkt->dts == AV_NOPTS_VALUE
	   && pFrame->opaque && *(uint64_t *)pFrame->opaque != AV_NOPTS_VALUE) {
	    pts = *(uint64_t *)pFrame->opaque;
	} else if(pkt->dts != AV_NOPTS_VALUE) {
	    pts = pkt->dts;	    
	} else {
	    pts = 0;
	}
	pts *= av_q2d(video->stream->time_base);
	if(frameFinished) {
//	    LOGI("decode completed!");
	    pts = sync_video(video, pFrame, pts);
	    if(video_frame_convert(video, pFrame, pts) < 0) {
		LOGE("video_frame_convert error!");
		break;
	    }
	}
	av_free_packet(pkt);
    }
    LOGE("decode thread exit");
    av_free(pFrame);
}


void alloc_frame(Media *video) {
    VideoFrame *vf;
    vf = &video->frame_buf[video->frame_convert_index];
    if(vf->bmp) {
	SDL_FreeYUVOverlay(vf->bmp);
	LOGW("realloc overlay");
    }
    vf->width = video->stream->codec->width;
    vf->height = video->stream->codec->height;

    if((vf->bmp = SDL_CreateYUVOverlay(vf->width, vf->height, SDL_YV12_OVERLAY, screen)) == NULL) {
	LOGE("fail to create YUV overlay ");
    } else {
	SDL_LockMutex(video->frame_buf_mutex);
	vf->allocated = 1;
	LOGI("frame allocated, num : %d", video->frame_convert_index);
	SDL_CondSignal(video->frame_buf_cond);
	SDL_UnlockMutex(video->frame_buf_mutex);
    }
}

void alloc_all_frame(Media *video) {
    video->frame_convert_index = 0;
    while(video->frame_convert_index < MAX_VIDEO_FRAME_BUF_SIZE) {
	alloc_frame(video);
	video->frame_convert_index++;
    }
    video->frame_convert_index = 0;
}

int video_frame_convert(Media *video, AVFrame *pFrame, double pts)
{
    AVPicture pict;
    int dstPixFmt;
    static struct SwsContext *imgConvertCtx;
    VideoFrame *vf;
    SDL_Event event;

    SDL_LockMutex(video->frame_convert_mutex);
    while(video->frame_buf_size >= MAX_VIDEO_FRAME_BUF_SIZE) {
//	LOGW("Frame buffer is full");
//	SDL_CondWait(video->frame_buf_cond, video->frame_buf_mutex);
	SDL_Delay(100);
    }
    vf = &video->frame_buf[video->frame_convert_index];
    SDL_UnlockMutex(video->frame_convert_mutex);
    // allocate or resize the buffer! 
    if(!vf->bmp ||
       vf->width != video->stream->codec->width ||
       vf->height != video->stream->codec->height) {
//	LOGE("bmp %x | frame (%d, %d) | codec (%d, %d) ", vf->bmp, vf->width, vf->height, video->stream->codec->width, video->stream->codec->height);
	vf->allocated = 0;
	//we have to do it in the main thread 
	event.type = FF_ALLOC_EVENT;
	event.user.data1 = video;
	SDL_PushEvent(&event);

	// wait until we have a picture allocated 
	SDL_LockMutex(video->frame_buf_mutex);
	while(!vf->allocated) {
	    LOGW("Waiting for alloc frame");
	    SDL_CondWait(video->frame_buf_cond, video->frame_buf_mutex);
	}
	SDL_UnlockMutex(video->frame_buf_mutex);
    }

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
	    int w = vf->width;
	    int h = vf->height;

#ifdef ORIGINAL_SIZE
	    imgConvertCtx = sws_getContext(w, h, video->stream->codec->pix_fmt,
					   vf->width, vf->height, dstPixFmt, SWS_FAST_BILINEAR, NULL, NULL, NULL);
#else
	    imgConvertCtx = sws_getContext(w, h, video->stream->codec->pix_fmt,					   
					   w, h, dstPixFmt, SWS_FAST_BILINEAR, NULL, NULL, NULL);
#endif //ORIGINAL_SIZE
	    if(imgConvertCtx == NULL) {
		LOGE("fail to init the conversion context : video_frame_convert");
		exit(-1);
	    }
	}
	sws_scale(imgConvertCtx, pFrame->data, pFrame->linesize, 0, vf->height, pict.data, pict.linesize);
	SDL_UnlockYUVOverlay(vf->bmp);

	vf->pts = pts;
	SDL_LockMutex(video->frame_convert_mutex);
	if(++video->frame_convert_index == MAX_VIDEO_FRAME_BUF_SIZE) {
	    video->frame_convert_index = 0;
	}	
//	SDL_LockMutex(video->frame_buf_mutex);
//	SDL_LockMutex(video->frame_buf_mutex);
	video->frame_buf_size++;
	SDL_UnlockMutex(video->frame_convert_mutex);
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
    video->frame_convert_index = 0;
    video->frame_display_index = 0;
    video->frame_timer = (double)av_gettime() / 1000000.0;
    video->frame_last_delay = 40e-3;
    video->find_stream = find_av_streams;
    video->find_codec = find_decoder;
    video->frame_buf_mutex = SDL_CreateMutex();
    video->frame_buf_cond = SDL_CreateCond();
    video->frame_convert_cond = SDL_CreateCond();    
    video->frame_convert_mutex = SDL_CreateMutex();    
    video->frame_last_delay = 40e-3;
    video->video_current_pts_time = av_gettime();
    video->frame_timer = (double)av_gettime() / 1000000.0;
    video->play = play_video;
    video->get_info = get_av_info;
}

