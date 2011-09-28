#ifndef __MESSAGE_H
#define __MESSAGE_H
#include <stdlib.h>


//used when receiving a message over a socket
struct message_partial {
    int len;
    char *buffer;
    int bufferSize;
    int bufferPos;
};
typedef struct message_partial message_partial;

struct message {
    int command;
    void *data;
};
typedef struct message message;

void message_partial_init(message_partial *mp);
int message_partial_is_complete(message_partial *mp);
message* message_partial_parse(message_partial *mp);
void message_partial_clear(message_partial *mp);
void message_partial_free(message_partial *mp);


struct message_send_message {
    int destUid;
    int timestamp;
    char *message;
};
typedef struct message_send_message message_send_message;

struct message_authenticate {
    int uuid;
    char *password;
    int version;
};
typedef struct message_authenticate message_authenticate;

struct message_get_roster {
};
typedef struct message_get_roster message_get_roster;
#endif
