#ifndef __QUEUE_H
#define __QUEUE_H
/*
 * Locking queue data structure
 */
#include "pqueue.h"
#include "queue.h"

struct queue {
    pqueue *pq;

    int readLock;
    int writeLock;
};
typedef struct queue queue;

extern void queue_init(queue *q, int (*compare)(void*, void*));
extern void* queue_top(queue *q);
extern void queue_pop(queue *q);
extern void queue_insert(queue *q, void *val);
#endif
