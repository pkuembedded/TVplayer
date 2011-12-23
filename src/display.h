#include "structures.h"
#include "config.h"

#ifndef DISPLAY_H
#define DISPLAY_H
SDL_Surface *screen;

int init_screen(Media *video);
int play_video(void *arg);
#endif //DISPLAY_H
