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
    File *file = av_mallocz(sizeof(File));
    Media *video = av_mallocz(sizeof(Media));
    Media *audio = av_mallocz(sizeof(Media));
    State *state = av_mallocz(sizeof(State));
    SDL_Thread *video_decode_tid;
    SDL_Thread *read_pkt_tid;
    SDL_Thread *play_tid;
    state->file = file;
    state->video = video;
    state->audio = audio;
    init_video(video);
    if(argc < 2) {
	fprintf(stderr, "Usage : play <file>\n");
	exit(1);
    }
    av_register_all();
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
	fprintf(stderr, "fail to initialize SDL - %s\n", SDL_GetError());
	exit(1);
    }
    av_strlcpy(file->name, argv[1], sizeof(file->name));
    get_file_info(file);
    find_av_streams(file, video, audio);
    find_decoder(video);
//    find_decoder(audio);
    init_screen(video);
    read_pkt_tid = SDL_CreateThread(queue_av_pkt, state);
    init_frame(video);
    video_decode_tid = SDL_CreateThread(decode_video, video);
//    video_refresh_timer(video);
    schedule_refresh(state, 40);
//    play_tid = SDL_CreateThread(play_video, video);
//    sleep(100);
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
