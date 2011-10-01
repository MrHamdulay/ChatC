#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "../queue.h"

int failed = 0;

int main() {
    queue list;
    queue_init(&list);
    test("Length 0 at creation", queue_len(&list) == 0);

    queue_append(&list, (void*)7);
    queue_remove(&list, list->pq);
    test("Empty removal", list->pq == NULL && queue_len(&list) == 0 && list.tail == NULL);

    for(int i=1; i<6; i++)
        queue_append(&list, (void *)i);
    test("Length assertion", (int)queue_len(&list) == 5);

    queue_node *cur = list->pq;
    int pass = 1;
    for(int i=1; i<6; i++) {
        if((int)cur->data != i)
            pass = 0;
        cur = cur->next;
    }
    test("Value assertion", pass);

    cur = list->pq;
    for(int i=0; i<4; i++)
        cur = cur->next;
    test("Tail check", cur == list.tail);

    for(int i=1; i<5; i++)
        cur = cur->prev;
    test("Reverse iteration", cur == list->pq);

    queue_prepend(&list, 0);
    test("Prepending", list->pq->data == 0);

    queue_remove(&list, list->pq);
    test("Remove", list->pq->data == 1);

    queue_remove(&list, list->pq->next);
    test("Removing", list->pq->data == 1);
    test("Removing", list->pq->next->data == 3);

    printf("\nNum failures: %d\n", failed);
}
