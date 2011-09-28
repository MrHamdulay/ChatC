#include <stdlib.h>
#include <time.h>
#include "llist.h"
#include "session.h"
#include "message.h"

void session_init(session *sess, int sock) {
    sess->startTime = time(NULL);
    sess->lastSeenTime = sess->startTime;
    sess->user = NULL;
    sess->sock = sock;
    sess->loggedIn = 0;

    message_partial_init(&sess->partialMessage);
    
    llist_init(&sess->sendMessageQueue);
}

void session_end(session *sess) {
    message_partial_free(&sess->partialMessage);
    free(sess->user);
}
