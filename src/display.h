#include "structures.h"

#ifndef DISPLAY_H
#define DISPLAY_H
SDL_Surface *screen;

int init_screen(Media *video);
void init_frame(Media *video);
#endif //DISPLAY_H
