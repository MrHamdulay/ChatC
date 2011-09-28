#include <stdlib.h>
#include "test.h"
#include "../pqueue.h"

int failed = 0;

struct data {
    int d;
};
typedef struct data data;

int compare_int(void *i1, void *i2) {
    return ((data*)i1)->d<((data*)i2)->d;
}

int main() {
    pqueue *q = (pqueue*)malloc(sizeof(pqueue));
    pqueue_init(q, compare_int);
    test("Heap null after initialisation", q->heap != NULL);

    data d[5] = {{1}, {2}, {3}, {4}, {5}};

    pqueue_insert(q, &d[4]);
    pqueue_insert(q, &d[1]);
    pqueue_insert(q, &d[3]);
    pqueue_insert(q, &d[0]);
    pqueue_insert(q, &d[2]);

    test("Queue size test", q->numElements == 5);
    test("min head test", ((data*)pqueue_top(q))->d == d[0].d);

    for(int i=0; i<4; i++) {
        pqueue_pop(q);
        test("remove test", ((data*)pqueue_top(q))->d == d[i+1].d);
    }
    pqueue_pop(q);
    test("empty test", pqueue_top(q) == NULL);
    test("empty test length", q->numElements == 0);

    pqueue_insert(q, &d[4]);
    test("single item test p1", ((data*)pqueue_top(q))->d == d[4].d);
    pqueue_pop(q);
    test("single item test p2", q->numElements == 0);

    for(int i=0; i<100; i++)
        pqueue_insert(q, &d[i%5]);
    test("massive test", q->numElements == 100);
    for(int i=0; i<100; i++) 
        pqueue_pop(q);

    return failed ? -1 : 0;
}
