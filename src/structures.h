#include "libffmpeg.h"
#include "libsdl.h"
#include "utility.h"


#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_NAME_LEN 1024
#define VIDEO_FRAME_QUEUE_SIZE 1


enum {
    AUDIO,
    VIDEO,
};
enum {
  AV_SYNC_AUDIO_MASTER,
  AV_SYNC_VIDEO_MASTER,
  AV_SYNC_EXTERNAL_MASTER,
};

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct VideoFrame {
    int width, height;
    int allocated;
    double pts;
    SDL_Overlay *bmp;
} VideoFrame;


typedef struct PacketQueue {
    AVPacketList *header, *end;
    int pkt_num;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;

typedef struct File {
    AVFormatContext *format_ctx;
    char name[MAX_NAME_LEN];
} File;


typedef struct Media {
    int media_type;
    int track;
    PacketQueue raw_data_buf;
    AVStream *stream;
    AVCodecContext *codec_ctx;
    AVCodec *codec;
    VideoFrame frame_buf;
    int frame_buf_size;
    double clk;
    double frame_timer;
    double frame_last_pts;
    double frame_last_delay;
    double video_current_pts;
    double video_current_pts_time;
    uint audio_buf_size;
    uint audio_buf_index;
    AVPacket audio_pkt;
    int audio_hw_buf_size;
    uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
    uint8_t *audio_pkt_data;
    int audio_pkt_size;
    SDL_mutex *frame_buf_mutex;
    SDL_mutex *frame_buf_cond;
    SDL_cond *play_cond;
    SDL_mutex *play_mutex;
    void (*init)(void *arg);
    void (*find_stream)(void *arg);
    int (*find_codec)(void *arg);
    int (*play)(void *arg);
    int (*pause)(void *arg);
} Media;


typedef struct State {
    File *file;
    Media *audio,*video;
} State;

#endif // STRUCTURES_H
