#include "display.h"

int init_screen(Media *video)
{
#ifdef ORIGINAL_SIZE
    screen = SDL_SetVideoMode(video->stream->codec->width, video->stream->codec->height, 0, 0);
#else
    screen = SDL_SetVideoMode(800, 350, 0, 0);
#endif //ORIGINAL_SIZE

    if(!screen) {
	LOGV("SDL: cannot init video mode : init_screen");
	exit(1);
    }
    return 0;
}

void init_frame(Media *video) {
    VideoFrame *vf;
    vf = &video->frame_buf[video->index];
    if(vf->bmp) {
	SDL_FreeYUVOverlay(vf->bmp);
    }
    vf->bmp = SDL_CreateYUVOverlay(video->stream->codec->width,
				   video->stream->codec->height,
				   SDL_YV12_OVERLAY,
				   screen);
    vf->width = video->stream->codec->width;
    vf->height = video->stream->codec->height;

    SDL_LockMutex(video->frame_buf_mutex);
    vf->allocated = 1;
    SDL_CondSignal(video->frame_buf_cond);
    SDL_UnlockMutex(video->frame_buf_mutex);
}

int play_video(void *arg)
{
    SDL_Rect rect;
    VideoFrame *vf;
    int w, h, x, y;
    float aspect_ratio;
    Media *video = (Media *)arg;
    vf = &video->frame_buf[video->frame_index];
    //put our pict on the queue
    if(vf->bmp)
    {
	if(video->stream->codec->sample_aspect_ratio.num == 0) {
	    aspect_ratio = 0;
	} else {
	    aspect_ratio = av_q2d(video->stream->codec->sample_aspect_ratio) * video->stream->codec->width / video->stream->codec->height;
	}
	if(aspect_ratio <= 0.0) {
	    aspect_ratio = (float)video->stream->codec->width / (float)video->stream->codec->height;
	}
	h = screen->h;
	w = ((int)rint(h * aspect_ratio)) & -3;
	if(w > screen->w) {
	    w = screen->w;
	    h = ((int)rint(w / aspect_ratio)) & -3;
	}
	x = (screen->w - w) / 2;
	y = (screen->h - h) / 2;
#ifdef ORIGINAL_SIZE
	rect.x = 0;
	rect.y = 0;
	rect.w = video->stream->codec->width;
	rect.h = video->stream->codec->height;
	SDL_DisplayYUVOverlay(vf->bmp, &rect);
#else
	rect.x = 0;
	rect.y = 0;
	rect.w = screen->w;
	rect.h = screen->h;
	SDL_DisplayYUVOverlay(vf->bmp, &rect);
#endif //ORIGINAL_SIZE
    }

    return 0;
}

