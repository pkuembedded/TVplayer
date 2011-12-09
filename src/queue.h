#include "structures.h"
#include "event.h"

#ifndef QUEUE_H
#define QUEUE_H

AVPacket flush_pkt;
void init_queue(PacketQueue *queue);
int add_to_queue(PacketQueue *queue, AVPacket *pkt);
int get_from_queue(PacketQueue *queue, AVPacket *pkt);
void queue_flush(PacketQueue *queue);
void quit();

#endif //QUEUE_H
