#include <stdlib.h>
#include <pthread.h>

#include "queue.h"
#include "pqueue.h"

void queue_init(queue *q, int (*compare)(void*, void*)) {
    q->pq = malloc(sizeof(pqueue));
    pqueue_init(q->pq, compare);

    pthread_mutex_init(&q->mutex, NULL);
}

void* queue_top(queue *q) {
    //cannot read while someone is writing
    pthread_mutex_lock(&q->mutex);
    void* ret =  pqueue_top(q->pq);
    pthread_mutex_unlock(&q->mutex);

    return ret;
}

void queue_pop(queue *q) {
    //cannot write while reading or writing

    pthread_mutex_lock(&q->mutex);
    pqueue_pop(q->pq);
    pthread_mutex_unlock(&q->mutex);
}

void queue_insert(queue *q, void *val) {
    pthread_mutex_lock(&q->mutex);
    pqueue_insert(q->pq, val);
    pthread_mutex_unlock(&q->mutex);
}
