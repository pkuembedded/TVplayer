#include "display.h"

int init_screen(Media *video)
{
    screen = SDL_SetVideoMode(video->codec_ctx->width, video->codec_ctx->height, 0, 0);
    if(!screen) {
	fprintf(stderr, "SDL: cannot init video mode : init_screen\n");
	exit(1);
    }
    return 0;
}

void init_frame(Media *video) {
    VideoFrame *vf;
    vf = &video->frame_buf;
    if(vf->bmp) {
	SDL_FreeYUVOverlay(vf->bmp);
    }
    vf->bmp = SDL_CreateYUVOverlay(video->stream->codec->width,
				   video->stream->codec->height,
				   SDL_YV12_OVERLAY,
				   screen);
    vf->width = video->stream->codec->width;
    vf->height = video->stream->codec->height;
}

int play_video(void *arg)
{
    SDL_Rect rect;
    VideoFrame *vf;
    int w, h, x, y;
    float aspect_ratio;
    Media *video = (Media *)arg;
    vf = &video->frame_buf;
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

	rect.x = 0;
	rect.y = 0;
	rect.w = video->codec_ctx->width;
	rect.h = video->codec_ctx->height;
	SDL_DisplayYUVOverlay(vf->bmp, &rect);
    }

    return 0;
}

