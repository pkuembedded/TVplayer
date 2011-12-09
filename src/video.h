#include "structures.h"
#include "queue.h"
#include "parse.h"
#include "config.h"

#ifndef VIDEO_H
#define VIDEO_H

#define VIDEO_FRAME_QUEUE_SIZE 1
uint64_t global_video_pkt_pts;

int video_frame_convert(Media *video, AVFrame *pFrame, double pts);
int decode_video(void *arg);
void our_release_buffer(AVCodecContext *codec_ctx, AVFrame *frame);
int our_get_buffer(AVCodecContext *codec_ctx, AVFrame *frame);
void init_video(Media *video);

#endif //VIDEO_H
