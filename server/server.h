#ifndef SERVER_H
#define SERVER_H

int init_server_socket(int *sock, int port);
void * handle_connection(void *csock);

#endif
