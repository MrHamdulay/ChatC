#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <time.h>

#include <pthread.h>

#include "server.h"
#include "config.h"
#include "../session.h"
#include "../llist.h"
#include "../queue.h"
#include "worker.h"

int sock;
int running;

void interrupt_handler(int signal) {
    printf("Caught signal\n");
    running = 0;
}

int check_for_connections(int sock) {
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    int csock = accept(sock, (struct sockaddr *)&client_addr, &clientlen);

    //set non blocking flag
    int flags = fcntl(csock, F_GETFL, 0);
    if(flags < 0) {
        printf("ERROR: Couldn't set socket flags\n");
        exit(1);
    }
    if(fcntl(csock, F_SETFL, flags | O_NONBLOCK)) {
        printf("ERROR: Couldn't set socket non-blocking\n");
        exit(1);
    }

    return csock;
}

void build_socket_list(llist *sessionList, fd_set *set) {
    FD_ZERO(set);
    llist_node *cur = sessionList->head;
    while(cur != NULL) {
        int sock = ((session*)cur->data)->sock;
        FD_SET(sock, set);
        cur = cur->next;
    }
}

//dummy comparison for priority queue
int dummy_cmp(void *i, void *i2) {
    return 1;
}

void client_read_data(session *sess) {
    char buffer[BUFFER_SIZE];
    int len = read(sess->sock, buffer, BUFFER_SIZE);
    message_partial *partial = &sess->partialMessage;

    for(int i=0; i<len; i++) {
        if(partial->bufferSize+1 >= partial->bufferPos+1) {
            partial->bufferSize *= 2;
            if(realloc(partial->buffer, partial->bufferSize) < 0) {
                printf("ERROR: Couldn't allocate enough memory for read buffer\n");
                exit(1);
            }
        }
        partial->buffer[partial->bufferPos++] = buffer[i];
    }

    //parse message
    if(message_partial_is_complete(partial)) {
        message *m = message_partial_parse(partial);
        //TODO: do something with the message

        //clear message buffer for next message to be received
        message_partial_clear(partial);
    }
}

int main() {
    running = 1;
    signal(SIGINT, interrupt_handler);
    printf("Starting server\n");

    if(!init_server_socket(&sock, PORT))
        return -1;

    //A linked list might not be the most efficient for this
    llist client_sessions;
    llist_init(&client_sessions);

    queue message_queue;
    queue_init(&message_queue);

    //TODO: initialise thread pool
    const int num_workers = 4;
    pthread_t workers[num_workers];
    for(int i=0; i<num_workers; i++) {
        pthread_create(&workers[i], NULL, worker_run, (void*)&message_queue);
    }
    
    //select stuff
    fd_set readsocketset;
    fd_set writesocketset;
    fd_set errorsocketset;
    struct timeval timeout;

    while(running) {
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;
        
        printf("1\n");
        build_socket_list(&client_sessions, &readsocketset);
        FD_SET(sock, &readsocketset);

        int s = select(client_sessions.len, &readsocketset, 0, 0, &timeout);
        printf("2\n");
        if(s < 0) {
            printf("ERROR: Select error\n");
            exit(1);
        }
        //if we have a new connection create a new session
        if(FD_ISSET(sock, &readsocketset)) {
            int csock = check_for_connections(sock);
            session clientSession;
            session_init(&clientSession, csock);
            llist_append(&client_sessions, (void*)&clientSession);
        }

        printf("2\n");
        //check if each session exists in the read socket thingE
        llist_node *cur = client_sessions.head;
        while(cur != NULL) {
            int sock = ((session*)cur->data)->sock;
            //check readsocketset
            if(FD_ISSET(sock, &readsocketset)) 
                client_read_data((session*)cur->data);
            //check writesocketset
            //check errorset
            cur = cur->next;
        }

        //TODO:
        //parse the messages
        //add parsed message to the queue

        //send messages on the queue (Should this be done here?)
    }
    printf("Exiting..\n");
    
    //free memory
    llist_node *cur = client_sessions.head;
    while(cur != NULL) {
        session *sess = (session*)cur->data;
        session_end(sess);
        free(sess);
        cur = cur->next;
    }
    llist_free(&client_sessions);
    close(sock);

    pthread_exit(NULL);
}
