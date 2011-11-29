#include "structures.h"
#ifndef QUEUE_H
#define QUEUE_H

void init_queue(PacketQueue *queue);
int add_to_queue(PacketQueue *queue, AVPacket *pkt);
int get_from_queue(PacketQueue *queue, AVPacket *pkt);
void queue_flush(PacketQueue *queue);

#endif //QUEUE_H
