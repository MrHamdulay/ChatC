#ifndef __NODES_H
#define __NODES_H
/*
 * Keep track of all online nodes
 */
#include "llist.h"

struct node {
    int socket;
    int status;
};
typedef struct node node;

struct nodes {
    llsit nodes;
};
typedef struct nodes node;

#endif
