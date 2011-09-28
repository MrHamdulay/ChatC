#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#include "config.h"

int init_server_socket(int *sock, int port) {
    struct sockaddr_in serv_addr;

    *sock = socket(AF_INET, SOCK_STREAM, 0);
    if(*sock < 0) {
        printf("ERROR: Unable to initialise socket\n");
        return 0;
    }

    //not sure how necessary
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if(bind(*sock, (struct sockaddr *) &serv_addr,
        sizeof(serv_addr)) < 0) {
        printf("ERROR: unable to bind to port: %d\n", port);
        return 0;
    }

    listen(*sock, 5);

    return 1;
}

void * handle_connection(void *csock) {
    int *socket = (int*) csock;
    printf("Got a new client connection %d\n", (int)*socket);
    return socket;
}
