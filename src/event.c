#include "structures.h"
#include "event.h"

void set_stop_flag(){
    if(stop_flag == true) 
	stop_flag = false;
    else
	stop_flag = true;
}

void quit(){
    SDL_Event event;
    event.type = FF_QUIT_EVENT;
    event.user.data1 = NULL;
    SDL_PushEvent(&event);
}

void refresh_event(void *opaque)
{
    SDL_Event event;
    event.type = FF_REFRESH_EVENT;
    event.user.data1 = opaque;
    SDL_PushEvent(&event);
}

void key_event(){
    Uint8 *key_states = SDL_GetKeyboardState(NULL);
    if(key_states[SDLK_ESCAPE])
	quit();
    else if(key_states[SDLK_SPACE])//新添加部分
	set_stop_flag();
}

void event_handle(SDL_Event *event){
    while(true) {
	SDL_WaitEvent(event);
	switch(event->type) {
	case FF_REFRESH_EVENT:
	    video_refresh(event->user.data1);
	    break;
	case SDL_KEYDOWN:
	    key_event();
	    break;
	case FF_ALLOC_EVENT:
	    alloc_frame(event->user.data1);
	    break;
	case FF_QUIT_EVENT:
	case SDL_QUIT:
	    exit(1);
	    break;
	default:
	    SDL_Delay(10);
	    break;
	}
    }
}
