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
    double delta;
    delta = (av_gettime() - video->video_current_pts_time) / 1000000.0;
    return video->video_current_pts + delta;
}

double get_external_clock() {
    return av_gettime() / 1000000.0;
}

double get_master_clock(State *state) 
{
    return get_video_clock(state->video);
}

int video_refresh_timer(void *arg)
{
    State *state = (State *)arg;
    VideoFrame *vf;
    double actual_delay, delay, sync_threshold, ref_clk, diff;
    if(state->video->stream) {
	if(state->video->frame_buf_size == 0) {
	    schedule_refresh(state, 1);
	} else {
	    vf = &state->video->frame_buf[state->video->frame_index];
	    state->video->video_current_pts = vf->pts;
	    state->video->video_current_pts_time = av_gettime();
	    delay = vf->pts - state->video->frame_last_pts;
	    if(delay <= 0 || delay >= 1.0) {
		delay = state->video->frame_last_delay;
	    }
	    state->video->frame_last_delay = delay;
	    state->video->frame_last_pts = vf->pts;
	    if(state->audio->stream) {
		ref_clk = get_audio_clock(state->audio);
		diff = vf->pts - ref_clk;
		sync_threshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
		if(fabs(diff) < AV_NOSYNC_THRESHOLD) {
		    if(diff <= -sync_threshold) {
			delay = 0;
		    } else if(diff > sync_threshold) {
			delay = 2 * delay;
		    }
		}
	    }
	    state->video->frame_timer += delay;
	    actual_delay = state->video->frame_timer - (av_gettime() / 1000000.0);
	    if(actual_delay < 0.010) {
		actual_delay = 0.010;
	    }
	    schedule_refresh(state, (int)(actual_delay * 50 + 0.5));
	    play_video(state->video);
	    if(++state->video->frame_index == VIDEO_FRAME_QUEUE_SIZE) {
		state->video->frame_index = 0;
	    }
	    SDL_LockMutex(state->video->frame_buf_mutex);
	    state->video->frame_buf_size--;
	    SDL_CondSignal(state->video->frame_buf_cond);
	    SDL_UnlockMutex(state->video->frame_buf_mutex);
	}
    } else {
	schedule_refresh(state, 100);
    }
    return 0;
}
