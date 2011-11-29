#include "display.h"

int init_screen(Media *video)
{
    screen = SDL_SetVideoMode(video->pCodecCtx->width, video->pCodecCtx->height, 0, 0);
    if(!screen) {
	fprintf(stderr, "SDL: cannot init video mode : init_screen\n");
	exit(1);
    }
    return 0;
}

void init_frame(Media *video) {
    VideoFrame *vf;
    vf = &video->frameBuf;
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

