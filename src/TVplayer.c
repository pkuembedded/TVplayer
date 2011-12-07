#include <stdio.h>
#include <math.h>
#include "structures.h"
#include "video.h"
#include "audio.h"
#include "sync.h"
#define VIDEO_FRAME_QUEUE_SIZE 1
#define FF_ALLOC_EVENT   (SDL_USEREVENT)
#define FF_REFRESH_EVENT (SDL_USEREVENT + 1)
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)

Media video, audio;
int main(int argc, char **argv)
{
    uint64_t global_video_pkt_pts;
    SDL_Surface *screen;
    SDL_Event event;
    Content *content = av_mallocz(sizeof(Content));
    Media *video = av_mallocz(sizeof(Media));
    Media *audio = av_mallocz(sizeof(Media));
    State *state = av_mallocz(sizeof(State));
    SDL_Thread *video_decode_tid;
    SDL_Thread *read_pkt_tid;
    SDL_Thread *play_tid;
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
    LOGI("initing screen");
    init_screen(video);
    LOGI("creating reading thread...");
    read_pkt_tid = SDL_CreateThread(queue_av_pkt, "read", state);
    init_frame(video);
    LOGI("creating decode thread...");
    video_decode_tid = SDL_CreateThread(decode_video, "decode", video);
    LOGI("schedule refreshing");
    schedule_refresh(state, 30);
    av_init_packet(&flush_pkt);
    flush_pkt.data = "FLUSH";
    while(true) {
	SDL_WaitEvent(&event);
	switch(event.type) {
	case FF_REFRESH_EVENT:
	    video_refresh_timer(event.user.data1);
	    break;
	default:
	    break;
	}
    }
    return 0;
}
