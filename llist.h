#ifndef __LLIST_H
#define __LLIST_H
struct llist_node {
    void *data;
    struct llist_node *next;
    struct llist_node *prev;
};
typedef struct llist_node llist_node;

struct llist {
    llist_node *head;
    llist_node *tail;
    int len;
};
typedef struct llist llist;

void llist_init(llist *list);
void llist_append(llist *list, void *data);
void llist_prepend(llist *list, void *data);
void llist_insert_after(llist *list, llist_node *prev, void *data);
void llist_free(llist *list);
int llist_remove(llist *list, llist_node *node);
#endif
