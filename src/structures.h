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
    int pktNum;
    int size;
    SDL_mutex *mutex;
    SDL_cond *cond;
} PacketQueue;

typedef struct File {
    AVFormatContext *pFormatCtx;
    char name[MAX_NAME_LEN];
} File;


typedef struct Media {
    int mediaType;
    int track;
    PacketQueue rawDataBuf;
    AVStream *stream;
    AVCodecContext *pCodecCtx;
    AVCodec *pCodec;
    VideoFrame frameBuf;
    int frameBufSize;
    double clk;
    double frame_timer;
    double frame_last_pts;
    double frame_last_delay;
    uint audio_buf_size;
    uint audio_buf_index;
    AVPacket audio_pkt;
    int audio_hw_buf_size;
    uint8_t audioBuf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];
    uint8_t *audioPktData;
    int audioPktSize;
    SDL_cond *playCond;
    SDL_mutex *playMutex;
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
