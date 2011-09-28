#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "../llist.h"

int failed = 0;

int main() {
    llist list;
    llist_init(&list);
    test("Length 0 at creation", list.len == 0);

    llist_append(&list, (void*)7);
    llist_remove(&list, list.head);
    test("Empty removal", list.head == NULL && list.len == 0 && list.tail == NULL);

    for(int i=1; i<6; i++)
        llist_append(&list, (void *)i);
    test("Length assertion", (int)list.len == 5);

    llist_node *cur = list.head;
    int pass = 1;
    for(int i=1; i<6; i++) {
        if((int)cur->data != i)
            pass = 0;
        cur = cur->next;
    }
    test("Value assertion", pass);

    cur = list.head;
    for(int i=0; i<4; i++)
        cur = cur->next;
    test("Tail check", cur == list.tail);

    for(int i=1; i<5; i++)
        cur = cur->prev;
    test("Reverse iteration", cur == list.head);

    llist_prepend(&list, 0);
    test("Prepending", list.head->data == 0);

    llist_remove(&list, list.head);
    test("Remove", list.head->data == 1);

    llist_remove(&list, list.head->next);
    test("Removing", list.head->data == 1);
    test("Removing", list.head->next->data == 3);

    printf("\nNum failures: %d\n", failed);
}
