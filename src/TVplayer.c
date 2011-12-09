#include <stdio.h>
#include <math.h>
#include "structures.h"
#include "video.h"
#include "audio.h"
#include "sync.h"
#include "event.h"
#include "config.h"

int main(int argc, char **argv)
{
    SDL_Event event;
    Content *content = av_mallocz(sizeof(Content));
    Media *video = av_mallocz(sizeof(Media));
    Media *audio = av_mallocz(sizeof(Media));
    State *state = av_mallocz(sizeof(State));
    SDL_Thread *video_decode_tid;
    SDL_Thread *read_pkt_tid;
    state->content = content;
    state->video = video;
    state->audio = audio;
    init_video(video);
    if(argc < 2) {
	LOGE("Usage : play <content>");
	exit(1);
    }
    av_register_all();
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
	LOGE("fail to initialize SDL");
	exit(1);
    }
    av_strlcpy(content->name, argv[1], sizeof(content->name));
    get_content_info(content);
    LOGI("finding streams");
    find_av_streams(content, video, audio);
    LOGI("finding decoder");
    find_decoder(video);
    video->get_info(video);

    LOGI("creating reading thread...");
    read_pkt_tid = SDL_CreateThread(queue_av_pkt, "read", state);
    LOGI("creating decode thread...");
    video_decode_tid = SDL_CreateThread(decode_video, "decode", video);
    LOGI("initing screen");
    init_screen(video);
    LOGI("schedule refreshing");
    schedule_refresh(state, 100);
    av_init_packet(&flush_pkt);
    flush_pkt.data = "FLUSH";
    while(true) {
	SDL_WaitEvent(&event);
	switch(event.type) {
	case FF_REFRESH_EVENT:
	    video_refresh_timer(event.user.data1);
	    break;
	case FF_QUIT_EVENT:
//	    SDL_Quit();
	    exit(1);
	    break;
	case FF_ALLOC_EVENT:
	    init_frame(event.user.data1);
	    break;
	default:
	    break;
	}
    }
    return 0;
}
