#include "sync.h"

double sync_video(Media *video, AVFrame *srcFrame, double pts) 
{
    double delay;
    if(pts != 0) {
	video->clk = pts;
    } else {
	pts = video->clk;
    }
    delay = av_q2d(video->stream->codec->time_base);
    delay += srcFrame->repeat_pict * (delay * 0.5);
    video->clk += delay;
    return pts;
}

static Uint32 sdl_refresh_timer_cb(Uint32 interval, void *opaque)
{
    SDL_Event event;
    event.type = FF_REFRESH_EVENT;
    event.user.data1 = opaque;
    SDL_PushEvent(&event);
    return 0; /* 0 means stop timer */
}

/* schedule a video refresh in 'delay' ms */
void schedule_refresh(State *state, int delay) {
    SDL_AddTimer(delay, sdl_refresh_timer_cb, state);
}

double get_audio_clock(Media *audio) {
    double pts;
    int hw_buf_size, bytes_per_sec, n;
    pts = audio->clk; /* maintained in the audio thread */
    hw_buf_size = audio->audio_buf_size - audio->audio_buf_index;
    bytes_per_sec = 0;
    n = audio->stream->codec->channels * 2;
    if(audio->stream) {
	bytes_per_sec = audio->stream->codec->sample_rate * n;
    }
    if(bytes_per_sec) {
	pts -= (double)hw_buf_size / bytes_per_sec;
    }
    return pts;
}
double get_video_clock(Media *video) {

}
double get_external_clock() {
    return av_gettime() / 1000000.0;
}

double get_master_clock(State *state) 
{
    return get_external_clock(state);
}


