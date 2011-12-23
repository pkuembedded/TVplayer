#include "libffmpeg.h"
#include "libsdl.h"
#include "utility.h"
#include "log.h"
//#include "threadpool.h"
#include <fcntl.h>
#include <stdlib.h>
#ifndef STRUCTURES_H
#define STRUCTURES_H

#define MAX_NAME_LEN 1024
#define MAX_VIDEO_FRAME_BUF_SIZE 50

enum {
    AUDIO,
    VIDEO,
};

enum {
  AV_SYNC_AUDIO_MASTER,
  AV_SYNC_VIDEO_MASTER,
  AV_SYNC_EXTERNAL_MASTER,
};


//#ifdef PC_TEST
//typedef unsigned int uint;
//#endif //PC_TEST
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

//struct content save info of the file or stream
typedef struct Content {
    AVFormatContext *format_ctx;
    int duration;
    char name[MAX_NAME_LEN];
} Content;

//Media is used to save info of either video or audio
typedef struct Media {
    int media_type;
    char info[MAX_NAME_LEN];//store A/V info
    int track;//track no.
    PacketQueue raw_data_buf;//raw data read from the file
    AVStream *stream;
    AVCodecContext *codec_ctx;
    AVCodec *codec;
    VideoFrame frame_buf[MAX_VIDEO_FRAME_BUF_SIZE];//store video frame after decode
    int frame_buf_size;
    int frame_convert_index;
    int frame_display_index;
    bool refresh;
    double clk;
    double frame_timer;
    double frame_last_pts;
    double frame_last_delay;
    double actual_delay;
    double video_current_pts;
    double video_current_pts_time;
    uint audio_buf_size;
    uint audio_buf_index;
    AVPacket audio_pkt;
    int audio_hw_buf_size;
    uint8_t audio_buf[(AVCODEC_MAX_AUDIO_FRAME_SIZE * 3) / 2];//store audio data after decode
    uint8_t *audio_pkt_data;
    int audio_pkt_size;
    double audio_diff_cum;
    double audio_diff_avg_coef;
    double audio_diff_threshold;
    int audio_diff_avg_count;

    SDL_mutex *frame_buf_mutex;
    SDL_cond *frame_buf_cond;

    SDL_mutex *frame_convert_mutex;
    SDL_cond *frame_convert_cond;

    void (*init)(void *arg);
    void (*find_stream)(void *arg);
    void (*get_info)(void *arg);
    int (*find_codec)(void *arg);
    int (*play)(void *arg);
    int (*pause)(void *arg);
} Media;

//State contain both video & audio
typedef struct State {
    Content *content;
    Media *audio,*video;
} State;

#endif // STRUCTURES_H
