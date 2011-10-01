#ifndef __QUEUE_H
#define __QUEUE_H
#include <pthread.h>
/*
 * Locking queue data structure
 */
#include "pqueue.h"
#include "queue.h"

struct queue {
    pqueue *pq;

    pthread_mutex_t mutex;
};
typedef struct queue queue;

extern void queue_init(queue *q, int (*compare)(void*, void*));
extern void* queue_top(queue *q);
extern void queue_pop(queue *q);
extern void queue_insert(queue *q, void *val);
#endif
