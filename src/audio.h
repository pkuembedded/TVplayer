#include "structures.h"
#include "parse.h"

#ifndef AUDIO_DECODE_H
#define AUDIO_DECODE_H


#define SDL_AUDIO_BUFFER_SIZE 1024


void init_audio(Media *audio);
int find_audio_decoder(Media *audio);
void audio_callback(void *userdata, Uint8 *stream, int len);
int decode_audio(Media *audio, uint8_t *audio_buf, int buf_size, double *pts_ptr);

#endif //AUDIO_DECODE_H
