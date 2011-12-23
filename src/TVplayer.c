#ifndef ANDROID

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
    SDL_Event *event = av_mallocz(sizeof(SDL_Event));
    Content *content = av_mallocz(sizeof(Content));
    Media *video = av_mallocz(sizeof(Media));
    Media *audio = av_mallocz(sizeof(Media));
    State *state = av_mallocz(sizeof(State));
    SDL_Thread *video_decode_tid1;
    SDL_Thread *video_decode_tid2;
    SDL_Thread *read_pkt_tid;
    SDL_Thread *refresh_tid;
//    InitPool(2);
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
    LOGE("addr : %x", video->frame_buf);
    get_content_info(content);
    LOGI("finding streams");
    find_av_streams(content, video, audio);
    LOGI("finding decoder");
    find_decoder(video);
    video->get_info(video);
    LOGI("creating reading thread...");
    read_pkt_tid = SDL_CreateThread(queue_av_pkt, "read", state);
    LOGI("initing screen");
    init_screen(video);
//    LOGI("alloc frame");
    alloc_frame(video);
    LOGI("alloc all the frame");
//    alloc_all_frame(video);
    LOGI("creating decode thread1...");
    video_decode_tid1 = SDL_CreateThread(decode_video, "decode1", video);    
    refresh(state, 50);
    event_handle(event);
    return 0;
}

#endif //ANDROID
