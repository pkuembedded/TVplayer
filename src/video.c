#include "video.h"
#include "sync.h"

int decode_video(void *arg)
{
    Media *video = (Media *)arg;
    AVFrame *pFrame;
    int frameFinished;
    double pts;
    AVPacket packet;
    AVPacket *pkt = &packet;
    pFrame = avcodec_alloc_frame();
    while(true) {
	if(get_from_queue(&video->rawDataBuf, pkt) < 0) {
	    fprintf(stderr, "fail to get video pkt from queue : decode_video\n");
	    break;
	}
	avcodec_decode_video2(video->pCodecCtx, pFrame, &frameFinished, &packet);
	pts = 0;
	global_video_pkt_pts = pkt->pts;
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
		break;;
//	    SDL_CondSignal(video->playCond);
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
    vf = &video->frameBuf;
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
		fprintf(stderr, "fail to init the conversion context : video_frame_queue\n");
		exit(-1);
	    }
	}
	sws_scale(imgConvertCtx, pFrame->data, pFrame->linesize, 0, video->stream->codec->height, pict.data, pict.linesize);
	SDL_UnlockYUVOverlay(vf->bmp);
	vf->pts = pts;
//	SDL_LockMutex(video->frameBuf->mutex);
	video->frameBufSize++;
//	SDL_UnlockMutex(video->frameBuf->mutex);
    }
    return 0;
}


int video_refresh_timer(void *arg)
{
    State *state = (State *)arg;
    VideoFrame *vf;
    double actual_delay, delay, sync_threshold, ref_clk, diff;
    if(state->video->stream) {
	if(state->video->frameBufSize == 0) {
	    schedule_refresh(state, 1);
	} else {
	    vf = &state->video->frameBuf;
	    delay = vf->pts - state->video->frame_last_pts;
	    if(delay <= 0 || delay >= 1.0) {
		delay = state->video->frame_last_delay;
	    }
	    state->video->frame_last_delay = delay;
	    state->video->frame_last_pts = vf->pts;

	    ref_clk = get_audio_clock(state->audio);
	    diff = vf->pts - ref_clk;
	    sync_threshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
	    if(fabs(diff) < AV_NOSYNC_THRESHOLD) {
		if(diff <= -sync_threshold) {
		    delay = 0;
		} else if(diff >= sync_threshold) {
		    delay = 2 * delay;
		}
	    }
	    state->video->frame_timer += delay;
	    actual_delay = state->video->frame_timer - (av_gettime() / 1000000.0);
	    if(actual_delay < 0.010) {
		actual_delay = 0.010;
	    }
	    schedule_refresh(state, (int)(actual_delay * 1000 + 0.5));
	    play_video(state->video);
	}
    } else {
	schedule_refresh(state, 100);
    }
    return 0;
}


void init_video(Media *video)
{
    memset(video, 0, sizeof(Media));
    global_video_pkt_pts = AV_NOPTS_VALUE;
    video->mediaType = VIDEO;
    video->frame_timer = (double)av_gettime() / 1000000.0;
    video->frame_last_delay = 40e-3;
    video->find_stream = find_av_streams;
    video->find_codec = find_decoder;
    video->play = play_video;
    video->playCond = SDL_CreateCond();    
    video->playMutex = SDL_CreateMutex();    
}


int play_video(void *arg)
{
    SDL_Rect rect;
    VideoFrame *vf;
    int w, h, x, y;
    Media *video = (Media *)arg;
    vf = &video->frameBuf;
    //put our pict on the queue
//    while(true) {
//	SDL_CondWait(video->playCond, video->playMutex);
	rect.x = 0;
	rect.y = 0;
	rect.w = video->pCodecCtx->width;
	rect.h = video->pCodecCtx->height;
//	video_refresh_timer(video);
	SDL_DisplayYUVOverlay(vf->bmp, &rect);
//    }
    return 0;
}

