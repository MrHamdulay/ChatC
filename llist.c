#include <stdlib.h>
#include <stdio.h>
#include "llist.h"

void llist_init(llist *list) {
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
}

llist_node* llist_node_new() {
    llist_node *n = malloc(sizeof(llist_node));
    n->data = NULL;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void llist_append(llist *list, void *data) {
    if(list->head == NULL) {
        list->head = llist_node_new();
        list->head->data = data;
    } else {
        llist_node *cur = list->head;
        while(cur->next != NULL)
            cur = cur->next;

        cur->next = llist_node_new();
        cur->next->prev = cur;
        cur = cur->next;
        cur->data = data;
        list->tail = cur;
    }
    list->len++;
}

void llist_prepend(llist *list, void *data) {
    llist_node *new = llist_node_new();
    new->data = data;

    llist_node *old = list->head;
    new->next = old;

    list->head = new;
    if(list->tail == NULL)
        list->tail = new;
    list->len++;
}

void llist_insert_after(llist *list, llist_node *prev, void *data) {
    llist_node *new = llist_node_new();
    new->data = data;

    new->next = prev->next;
    prev->next = new;
    new->prev = prev;
    if(prev == list->tail)
        list->tail = new;
    list->len++;
}

int llist_remove(llist *list, llist_node *node) {
    if(list->head == node)
        list->head = list->head->next;
    if(list->tail == node)
        list->tail = node->prev;

    llist_node *prev = node->prev;
    if(prev) 
        prev->next = node->next;

    llist_node *next = node->next;
    if(next && prev)
        next->prev = prev;

    free(node);
    list->len--;
    return 1;
}

void llist_free(llist *list) {
    //TODO: this
}
