#include "structures.h"

#ifndef PARSE_H
#define PARSE_H

#define MAX_VIDEO_QUEUE_SIZE (50 * 256 * 1024)
#define MAX_AUDIO_QUEUE_SIZE (50 * 16 * 1024)

int get_content_info(Content *content);
void find_av_streams(Content *content, Media *video, Media *audio);
int find_decoder(Media *media);
int queue_av_pkt(void *arg);
void get_av_info(void *arg);
#endif //PARSE_H
