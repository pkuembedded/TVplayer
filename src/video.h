#include "structures.h"
#include "file.h"

#ifndef VIDEO_H
#define VIDEO_H

#define VIDEO_FRAME_QUEUE_SIZE 1

int video_frame_convert(Media *video, AVFrame *pFrame, double pts);
int decode_video(void *arg);
void init_video(Media *video);

#endif //VIDEO_H
