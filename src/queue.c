#include "queue.h"


void init_queue(PacketQueue *queue)
{
    memset(queue, 0, sizeof(PacketQueue));
    queue->mutex = SDL_CreateMutex();
    queue->cond = SDL_CreateCond();
}


int add_to_queue(PacketQueue *queue, AVPacket *pkt)
{
    AVPacketList *pkt1;
    if(!(pkt1 = av_malloc(sizeof(AVPacketList))))
    {
	fprintf(stderr, "fail to malloc : add_to_queue\n");
	return -1;	    
    }
    if(pkt != &flush_pkt && av_dup_packet(pkt) < 0)
    {
	fprintf(stderr, "av_dup_packet : add_to_queue\n");
	return -1;	    
    }

    pkt1->pkt = *pkt;
    pkt1->next = NULL;
    SDL_LockMutex(queue->mutex);
    if(!queue->end)
	queue->header = pkt1;
    else
	queue->end->next = pkt1;
    queue->end = pkt1;
    queue->pkt_num++;
    queue->size += pkt1->pkt.size;
    SDL_CondSignal(queue->cond);
    SDL_UnlockMutex(queue->mutex);
    return 0;
}


int get_from_queue(PacketQueue *queue, AVPacket *pkt)
{
    AVPacketList *pkt1;
    int ret;
    SDL_LockMutex(queue->mutex);
    while(true) {
	pkt1 = queue->header;
	if(pkt1) {
//	    fprintf(stderr, "video queue size :%d, video queue pkt_num: %d\n", queue->size, queue->pkt_num);
	    queue->header = queue->header->next;
	    if(!queue->header)
		queue->end = NULL;
	    queue->pkt_num--;
	    queue->size -= pkt1->pkt.size;
	    *pkt = pkt1->pkt;
	    av_free(pkt1);
	    ret = 1;
	    break;
	}else {
//	    fprintf(stderr, "video queue size :%d, video queue pkt_num: %d\n", queue->size, queue->pkt_num);
	    SDL_CondWait(queue->cond, queue->mutex);
	}
    }
    SDL_UnlockMutex(queue->mutex);
    return ret;
}


void queue_flush(PacketQueue *queue)
{
    AVPacketList *pkt, *pkt1;
    SDL_LockMutex(queue->mutex);
    for (pkt = queue->header; pkt != NULL; pkt = pkt1) {
	pkt1 = pkt->next;
	av_free_packet(&pkt->pkt);
	av_freep(&pkt);
    }
    queue->header = NULL;
    queue->end = NULL;
    queue->pkt_num = 0;
    queue->size = 0;
    SDL_UnlockMutex(queue->mutex);
}

