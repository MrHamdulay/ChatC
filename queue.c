#include <stdlib.h>

#include "queue.h"
#include "pqueue.h"

void queue_init(queue *q, int (*compare)(void*, void*)) {
    q->pq = malloc(sizeof(pqueue));
    pqueue_init(q->pq, compare);
    q->readLock = 0;
    q->writeLock = 0;
}

void* queue_top(queue *q) {
    //cannot read while someone is writing
    while(q->writeLock != 0);

    q->readLock++;
    void* ret =  pqueue_top(q->pq);
    q->readLock--;

    return ret;
}

void queue_pop(queue *q) {
    //cannot write while reading or writing
    while(q->writeLock != 0 || q->readLock != 0);
    q->readLock++;
    q->writeLock++;

    pqueue_pop(q->pq);

    q->readLock--;
    q->writeLock--;
}

void queue_insert(queue *q, void *val) {
    //cannot write while reading or writing
    while(q->writeLock != 0 || q->readLock != 0);
    q->readLock++;
    q->writeLock++;

    pqueue_insert(q->pq, val);

    q->readLock--;
    q->writeLock--;
}
