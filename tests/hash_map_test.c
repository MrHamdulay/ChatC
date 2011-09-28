#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "../hash_map.h"

int failed = 0;

int fake_hash(void *k) {
    return *(int*)k%3;
}

void print_list() {
}

int main() {
    hash_map hm;
    hash_map_init(&hm, default_comp, fake_hash, 100);

    int data[5][2] = {{1,2},{3,4},{4,5},{2,3},{5,6}};
    for(int i=0; i<5; i++) {
        hash_map_insert(&hm, &data[i][0], &data[i][1]);
    }
    int passed = 1;
    for(int i=0; i<5; i++)
        if(!hash_map_contains(&hm, &data[i][0]))
            passed = 0;
    test("Contains",passed == 1);

    passed = 1;
    for(int i=4; i>=0; i--) {
        if(*(int*)hash_map_lookup(&hm, &data[i][0]) != data[i][1])
            passed = 0;
    }
    test("Lookup", passed == 1);
    hash_map_remove(&hm, &data[1][0]);
    test("Remove", hash_map_lookup(&hm, &data[1][0]) == NULL);

    for(int i=0; i<5; i++) {
        printf("Box index %d\n", i);
        llist_node *cur = hm.boxes[i]->head;
        while(cur != NULL) {
            hash_item *item = (hash_item*)cur->data;
            printf("\t%d  %d\n", *(int*)item->key, *(int*)item->value);
            cur = cur->next;
        }
    }
}
