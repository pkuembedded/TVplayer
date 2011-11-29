#include "structures.h"
#ifndef SYNC_H
#define SYNC_H

#define FF_ALLOC_EVENT   (SDL_USEREVENT)
#define FF_REFRESH_EVENT (SDL_USEREVENT + 1)
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)

double sync_video(Media *video, AVFrame *srcFrame, double pts);
static Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque);
void schedule_refresh(State *state, int delay);
double get_audio_clock(Media *audio);
double get_video_clock(Media *video);
double get_video_clock(Media *video);
double get_external_clock();

#endif //SYNC_H
