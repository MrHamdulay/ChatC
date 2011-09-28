#ifndef __ROSTER_H
#define __ROSTER_H
#include "hash_map.h"

/*
 * Keep track of the user roster
 */
struct roster {
    hash_map hm;
};

typedef struct roster roster;

//Check if user registered
int roster_user_exists(roster *r, int uid);

//Last online (unix timestamp)
int roster_user_last_online(roster *r, int uid);

//User logged into this node?
int roster_user_is_local(roster *r, int uid);

//Node user is logged into
int roster_user_node(roster *r, int uid);
#endif
