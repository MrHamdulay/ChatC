#ifndef __HASH_MAP_C
#define __HASH_MAP_C
#include "llist.h"

//TODO: add support to increase number of boxes when it gets too big
//will need to recreate entire map though :/
//start with a largish numebr

struct hash_map {
    //hash equal comparison function
    int (*comp)(void *i1, void *i2);
    //hash function
    int (*hash)(void *i);

    //list of linked lists containing all items as hash_item's
    llist **boxes;
    int hashLength; //hashLength = len(boxes)
};
typedef struct hash_map hash_map;

struct hash_item {
    void *key;
    void *value;
};
typedef struct hash_item hash_item;

void hash_map_init(hash_map *hm, int (*comp)(void*, void*), 
                   int (*hash)(void*), int hashLength);
void* hash_map_lookup(hash_map *hm, void *key);
void hash_map_insert(hash_map *hm, void *key, void *value);
int hash_map_remove(hash_map *hm, void *key);
int hash_map_contains(hash_map *hm, void *key);
void hash_map_free(hash_map *hm);

int hash_int_hash(void *k);
int default_comp(void *h1, void *h2);
#endif
