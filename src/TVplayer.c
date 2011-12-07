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
    fp = fopen(LOG_FILE, "w");
    if(!fp) {
	fprintf(stderr, "fail to open log file\n");
	exit(1);
    }
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
	LOGW("Usage : play <content>");
	exit(1);
    }
    av_register_all();
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
	LOGV("fail to initialize SDL");
	exit(1);
    }
    av_strlcpy(content->name, argv[1], sizeof(content->name));
    get_content_info(content);
    LOGV("finding streams");
    find_av_streams(content, video, audio);
    LOGV("finding decoder");
    find_decoder(video);
    video->get_info(video);
    LOGV("initing screen");
    init_screen(video);
    LOGV("creating reading thread...");
    read_pkt_tid = SDL_CreateThread(queue_av_pkt, "read", state);
    init_frame(video);
    LOGV("creating decode thread...");
    video_decode_tid = SDL_CreateThread(decode_video, "decode", video);
    LOGV("schedule refreshing");
    schedule_refresh(state, 30);
    av_init_packet(&flush_pkt);
    flush_pkt.data = "FLUSH";
    while(true) {
	SDL_WaitEvent(&event);
	switch(event.type) {
	case FF_REFRESH_EVENT:
//	    LOGV("refresh event");
	    video_refresh_timer(event.user.data1);
	    break;
	default:
	    break;
	}
    }
    fclose(fp);
    return 0;
}
