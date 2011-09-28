pqueue:
	gcc -o pqueue.o ../pqueue.c -c -g -std=c99
	gcc -o pqueue_test.o pqueue_test.c -c -g -std=c99
	gcc -o pqueue_test pqueue_test.o pqueue.o -g -std=c99

llist:
	gcc -o llist.o ../llist.c -c -g -std=c99 -Wall
llist_test: llist
	gcc -o llist_test.o llist_test.c -c -g -std=c99 -Wall
	gcc -o llist_test llist_test.o llist.o -g -std=c99 -Wall

hash_map: llist
	gcc -o hash_map.o ../hash_map.c -c -g -std=c99 -Wall
	gcc -o hash_map_test.o hash_map_test.c -c -g -std=c99 -Wall
	gcc -o hash_map_test hash_map.o hash_map_test.o llist.o -g -std=c99 -Wall

all: pqueue llist hash_map
