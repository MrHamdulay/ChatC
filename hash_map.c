#include <stdlib.h>
#include <assert.h>
#include "llist.h"
#include "hash_map.h"

void hash_map_init(hash_map *hm, int (*comp)(void*, void*), 
                   int (*hash)(void*), int hashLength) {
    hm->comp = comp;
    hm->hash = hash;
    hm->boxes = malloc(sizeof(llist*)*hashLength);
    for(int i=0; i<hashLength; i++) {
        hm->boxes[i] = malloc(sizeof(llist));
        llist_init(hm->boxes[i]);
    }
    hm->hashLength = hashLength;
}

void* hash_map_lookup(hash_map *hm, void *key) {
    int hash = hm->hash(key);

    llist_node *cur = hm->boxes[hash]->head;
    while(cur != NULL) {
        if(hm->comp(((hash_item*)cur->data)->key, key)) {
            return ((hash_item*)cur->data)->value;
        }
        cur = cur->next;
    }
    return NULL;
}

//doesn't check for key collisions
void hash_map_insert(hash_map *hm, void *key, void *value) {
    int hash = hm->hash(key);
    assert(hash < hm->hashLength);

    hash_item *item = malloc(sizeof(hash_item));
    item->key = key;
    item->value = value;

    llist_append(hm->boxes[hash], item);
}

int hash_map_remove(hash_map *hm, void *key) {
    int hash = hm->hash(key);
    assert(hash < hm->hashLength);

    llist_node *cur = hm->boxes[hash]->head;
    while(cur != NULL) {
        if(hm->comp(((hash_item*)cur->data)->key, key))
            break;
        cur = cur->next;
    }
    if(cur != NULL)
        return llist_remove(hm->boxes[hash], cur);
    return 0;
}

int hash_map_contains(hash_map *hm, void *key) {
    return hash_map_lookup(hm, key) != NULL;
}

void hash_map_free(hash_map *hm) {
    for(int i=0; i<hm->hashLength; i++) 
        llist_free(hm->boxes[i]);
    free(hm->boxes);
}

//uses default hash length of 100
int hash_int_hash(void *k) {
    return (*(int*)k)*(*(int*)k) % 100;
}

int default_comp(void *h1, void *h2) {
    return *(int*)h1 == *(int*)h2;
}
