#include "structures.h"
#include "event.h"

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
}

void event_handle(){
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch(event.type) {
    case FF_REFRESH_EVENT:
	video_refresh_timer(event.user.data1);
	break;
	case SDL_KEYDOWN:
            key_event();
	    break;
    case FF_ALLOC_EVENT:
	init_frame(event.user.data1);
	break;

    case FF_QUIT_EVENT:
    case SDL_QUIT:
	exit(1);
	break;
    default:
	break;
    }	
}

