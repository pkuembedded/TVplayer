#ifndef EVENT_H
#define EVENT_H

#define FF_ALLOC_EVENT   (SDL_USEREVENT)
#define FF_REFRESH_EVENT (SDL_USEREVENT + 1)
#define FF_QUIT_EVENT (SDL_USEREVENT + 2)

void quit();
void refresh_event(void *opaque);
void event_handle();

#endif //EVENT_H
