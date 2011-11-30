#include "structures.h"
#ifndef SYNC_H
#define SYNC_H

#define FF_ALLOC_EVENT   (SDL_USEREVENT)
#define FF_REFRESH_EVENT (SDL_USEREVENT + 1)
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)
#define AV_SYNC_THRESHOLD 0.01
#define AV_NOSYNC_THRESHOLD 10.0


double sync_video(Media *video, AVFrame *srcFrame, double pts);
static Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque);
void schedule_refresh(State *state, int delay);
double get_audio_clock(Media *audio);
double get_video_clock(Media *video);
double get_external_clock();
int video_refresh_timer(void *arg);

#endif //SYNC_H
