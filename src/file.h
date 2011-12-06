#include "structures.h"

#ifndef FILE_H
#define FILE_H
uint64_t global_video_pkt_pts;

#define MAX_VIDEO_QUEUE_SIZE (10 * 256 * 1024)
#define MAX_AUDIO_QUEUE_SIZE (10 * 16 * 1024)


int our_get_buffer(AVCodecContext *codec_ctx, AVFrame *frame);
void our_release_buffer(AVCodecContext *codec_ctx, AVFrame *frame);
int get_file_info(File *file);
void find_av_streams(File *file, Media *video, Media *audio);
int find_decoder(Media *media);
int queue_av_pkt(void *arg);
void get_av_info(void *arg);
#endif //FILE_H
