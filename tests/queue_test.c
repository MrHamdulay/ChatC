#include <stdlib.h>
#include "test.h"
#include "../queue.h"

int failed = 0;

struct data {
    int d;
};
typedef struct data data;

int compare_int(void *i1, void *i2) {
    return ((data*)i1)->d<((data*)i2)->d;
}

//TODO: do locking tests

int main() {
    queue *q = (queue*)malloc(sizeof(queue));
    queue_init(q, compare_int);
    test("Heap null after initialisation", q->pq->heap != NULL);

    data d[5] = {{1}, {2}, {3}, {4}, {5}};

    queue_insert(q, &d[4]);
    queue_insert(q, &d[1]);
    queue_insert(q, &d[3]);
    queue_insert(q, &d[0]);
    queue_insert(q, &d[2]);

    test("Queue size test", q->pq->numElements == 5);
    test("min head test", ((data*)queue_top(q))->d == d[0].d);

    for(int i=0; i<4; i++) {
        queue_pop(q);
        test("remove test", ((data*)queue_top(q))->d == d[i+1].d);
    }
    queue_pop(q);
    test("empty test", queue_top(q) == NULL);
    test("empty test length", q->pq->numElements == 0);

    queue_insert(q, &d[4]);
    test("single item test p1", ((data*)queue_top(q))->d == d[4].d);
    queue_pop(q);
    test("single item test p2", q->pq->numElements == 0);

    for(int i=0; i<100; i++)
        queue_insert(q, &d[i%5]);
    test("massive test", q->pq->numElements == 100);
    for(int i=0; i<100; i++) 
        queue_pop(q);

    return failed ? -1 : 0;
}
