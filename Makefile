all:
	rm -Rf *.o
	clang -c pqueue.c -Wall -ggdb
	clang -c server/server.c -Wall -ggdb
	clang -c server/worker.c -Wall -ggdb
	clang -c server/main.c -Wall -ggdb
	clang -c llist.c -Wall -ggdb
	clang -c session.c -Wall -ggdb
	clang -c queue.c -Wall -ggdb
	clang -c message.c -Wall -ggdb
	cd ..
	clang -o mserver server.o main.o pqueue.o session.o llist.o queue.o message.o worker.o -pthread -Wall
