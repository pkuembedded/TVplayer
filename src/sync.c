#include "sync.h"
#include "event.h"
#include <unistd.h>

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
    return 0; 
}

// schedule a video refresh in 'delay' ms 
void schedule_refresh(State *state, int delay) {
    SDL_AddTimer(delay, sdl_refresh_timer_cb, state);
}

void refresh(void *arg, int delay) {
    State *state = (State *)arg;
    SDL_AddTimer(delay, sdl_refresh_timer_cb, state);
}

double get_audio_clock(Media *audio) {
    double pts;
    int hw_buf_size, bytes_per_sec, n;
    pts = audio->clk; // maintained in the audio thread 
    hw_buf_size = audio->audio_buf_size - audio->audio_buf_index;
    bytes_per_sec = 0;
    n = audio->stream->codec->channels*2;
    if(audio->stream) {
	bytes_per_sec = audio->stream->codec->sample_rate*n;
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

double get_master_clock() {
    return get_external_clock();
}

void video_refresh(void *arg)
{
    State *state = (State *)arg;
    VideoFrame *vf;
    double actual_delay, delay, sync_threshold, ref_clk, diff;
    if(state->video->stream) {
	if(state->video->frame_buf_size == 0) {
	    LOGE("refresh 1");
	    refresh(state, 1);
	} else {
	    vf = &state->video->frame_buf[state->video->frame_display_index];
	    state->video->video_current_pts = vf->pts;
	    state->video->video_current_pts_time = av_gettime();
	    delay = vf->pts - state->video->frame_last_pts;
	    if(delay <= 0 || delay >= 1.0) {
		delay = state->video->frame_last_delay;
	    }
	    state->video->frame_last_delay = delay;
	    state->video->frame_last_pts = vf->pts;
	    ref_clk = get_external_clock();
	    diff = vf->pts - ref_clk;
	    sync_threshold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
	    if(fabs(diff) < AV_NOSYNC_THRESHOLD) {
		if(diff <= -sync_threshold) {
		    delay = 0;
		} else if(diff > sync_threshold) {
		    delay = 2 * delay;
		}
	    }
	    state->video->frame_timer += delay;
	    actual_delay = state->video->frame_timer - (av_gettime() / 1000000.0);
	    if(actual_delay < 0.010) {
		actual_delay = 0.010;
	    }
	    refresh(state, (int)(actual_delay * 1000) + 0.5);
	    LOGI("%s : %d", "delay", (int)(actual_delay * 1000 + 0.5));
 	    LOGW("frame buffer size : %d", state->video->frame_buf_size);
//	    LOGW("convert : %d", state->video->frame_convert_index);
//	    LOGW("display : %d", state->video->frame_display_index);
	    play_video(state->video);
	    if(++state->video->frame_display_index == MAX_VIDEO_FRAME_BUF_SIZE) {
		state->video->frame_display_index = 0;
	    }
	    SDL_LockMutex(state->video->frame_buf_mutex);
	    state->video->frame_buf_size--;
	    SDL_CondSignal(state->video->frame_buf_cond);
	    SDL_UnlockMutex(state->video->frame_buf_mutex);
	}
    }
}


int sync_audio(Media *audio, short *samples, int samples_size, double pts) 
{
    int n;
    double ref_clk;
    n = 2*audio->stream->codec->channels;
    double diff, avg_diff;
    int wanted_size, min_size, max_size, nb_samples;
    ref_clk = get_master_clock();
    diff = get_audio_clock(audio) - ref_clk;
    if(diff < AV_NOSYNC_THRESHOLD) {
	audio->audio_diff_cum = diff + audio->audio_diff_avg_coef * audio->audio_diff_cum;
	if(audio->audio_diff_avg_count < AUDIO_DIFF_AVG_NB) {
	    audio->audio_diff_avg_count++;
	} else {
	    avg_diff = audio->audio_diff_cum * (1.0 - audio->audio_diff_avg_coef);
	    if(fabs(avg_diff) >= audio->audio_diff_threshold) {
		wanted_size = samples_size + ((int)(diff * audio->stream->codec->sample_rate) * n);
		min_size = samples_size * ((100 - SAMPLE_CORRECTION_PERCENT_MAX) / 100);
		max_size = samples_size * ((100 + SAMPLE_CORRECTION_PERCENT_MAX) / 100);
		if(wanted_size < min_size) {
		    wanted_size = min_size;
		} else if (wanted_size > max_size) {
		    wanted_size = max_size;
		}
		if(wanted_size < samples_size) {

		    samples_size = wanted_size;
		} else if(wanted_size > samples_size) {
		    uint8_t *samples_end, *q;
		    int nb;
		    nb = (samples_size - wanted_size);
		    samples_end = (uint8_t *)samples + samples_size - n;
		    q = samples_end + n;
		    while(nb > 0) {
			memcpy(q, samples_end, n);
			q += n;
			nb -= n;
		    }
		    samples_size = wanted_size;
		}
	    }
	}
    } else {
	audio->audio_diff_avg_count = 0;
	audio->audio_diff_cum = 0;
    }
    return samples_size;
}
