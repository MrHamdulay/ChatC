#ifndef PQUEUE_H
#define PQUEUE_H

typedef struct node node;

struct pqueue {
    char id[3];
    int (*compare)(void*, void*);

    //list of pointers to object
    void **heap;
    int numElements;
    int size;
};
typedef struct pqueue pqueue;

//asumes comparing between to int's
//return n1 < n2
extern int compare_default(void *n1, void *n2);
extern void pqueue_init(pqueue *q, int (*compare)(void*, void*));
extern void* pqueue_top(pqueue *q);
extern void pqueue_pop(pqueue *q);
extern void pqueue_insert(pqueue *q, void *val);

#endif
