//priority queue used for scheduling
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "pqueue.h"

//parent = (i-1)/2
//children = 2i+1 and 2i+2

//TODO: thread safety

void pqueue_increase(struct pqueue *q) {
    q->size *= 2;
    q->heap = realloc(q->heap, q->size*sizeof(void*));
    if(q->heap == NULL) {
        printf("ERROR: unable to reallocate pqueue heap size: %d\n", q->size);
        exit(-1);
    }
}

void pqueue_init(struct pqueue *q, int (*compare)(void*, void*)) {
    q->compare = compare;

    q->numElements = 0;
    q->size = 8;
    q->heap = NULL;
    pqueue_increase(q);
}

void* pqueue_top(pqueue *q) {
    return (q->numElements == 0) ? NULL : q->heap[0];
}

void swap(pqueue *q, int s1, int s2) {
    void *temp = q->heap[s1];
    q->heap[s1] = q->heap[s2];
    q->heap[s2] = temp;
}

void pqueue_pop(pqueue *q) {
    //put element at the bottom as root
    q->heap[0] = q->heap[--q->numElements];
    //percolate down
    int cur = 0;
    //ensure that the compares are the right way around
    while(1) {
        if(cur*2+1 > q->numElements)
            break;

        //if we have one left child
        if(cur*2+1 == q->numElements) {
            if(!q->compare(q->heap[cur], q->heap[2*cur+1]))
                swap(q, cur, 2*cur+1);
            break;
        }

        //if heap property is satisfied yaaay
        if(q->compare(q->heap[cur], q->heap[2*cur+1]) && q->compare(q->heap[cur], q->heap[2*cur+2]))
            break;

        //do swaps
        if(q->compare(q->heap[2*cur+1], q->heap[2*cur+2])) {
            swap(q, 2*cur+1, cur);
            cur = 2*cur+1;
        } else {
            swap(q, 2*cur+2, cur);
            cur = 2*cur+2;
        }
    }
}

void pqueue_insert(pqueue *q, void *val) {
    assert(val != NULL);
    if(q->numElements+1 > q->size) {
        printf("We need to increase in size!\n");
        pqueue_increase(q);
    }
    q->heap[q->numElements] = val;

    int cur = q->numElements;
    //TODO: ensure that this is the correct direction
    while(q->compare(q->heap[cur], q->heap[(cur-1)/2])) {
        swap(q, cur, (cur-1)/2);
        //make parent current
        cur = (cur-1)/2;
    }
    q->numElements++;
}

