#include "structures.h"
#include "file.h"

#ifndef VIDEO_H
#define VIDEO_H
#define AV_SYNC_THRESHOLD 0.01
#define AV_NOSYNC_THRESHOLD 10.0

int video_frame_convert(Media *video, AVFrame *pFrame, double pts);
int decode_video(void *arg);
int video_refresh_timer(void *arg);
int play_video(void *arg);
void init_video(Media *video);

#endif //VIDEO_H
