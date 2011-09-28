#ifndef __SESSION_H
#define __SESSION_H
#include "user.h"
#include "llist.h"
#include "message.h"

struct session {
    int startTime; 
    int lastSeenTime;

    int loggedIn; //boolean
    user *user;

    int version; //client protocol version
    int sock;
    message_partial partialMessage;

    llist sendMessageQueue;
};
typedef struct session session;

void session_init(session *sess, int sock);
void session_end(session *sess);
#endif
