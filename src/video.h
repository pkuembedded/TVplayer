#include "structures.h"
#include "queue.h"
#include "parse.h"
#include "config.h"

#ifndef VIDEO_H
#define VIDEO_H
typedef struct {
    Media *video;
    double pts;
    AVFrame *pFrame;
}OneFrame;

unsigned long int global_video_pkt_pts;
void alloc_frame(Media *video);
int video_frame_convert(Media *video, AVFrame *pFrame, double pts);
void decode_video(void *arg);
void our_release_buffer(AVCodecContext *codec_ctx, AVFrame *frame);
int our_get_buffer(AVCodecContext *codec_ctx, AVFrame *frame);
void init_video(Media *video);

#endif //VIDEO_H
