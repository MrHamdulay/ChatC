#include <stdlib.h>
#include <pthread.h>

#include "queue.h"
#include "llist.h"

void queue_init(queue *q) {
    q->pq = malloc(sizeof(llist));
    llist_init(q->pq);

    pthread_mutex_init(&q->mutex, NULL);
}

void* queue_top(queue *q) {
    pthread_mutex_lock(&q->mutex);
    void *ret = q->pq->head->data;
    pthread_mutex_unlock(&q->mutex);

    return ret;
}

void queue_pop(queue *q) {
    //cannot write while reading or writing

    pthread_mutex_lock(&q->mutex);
    llist_remove(q->pq, q->pq->tail);
    pthread_mutex_unlock(&q->mutex);
}

void queue_insert(queue *q, void *val) {
    pthread_mutex_lock(&q->mutex);
    llist_append(q->pq, val);
    pthread_mutex_unlock(&q->mutex);
}

int queue_len(queue *q) {
    return q->pq->len;
}
