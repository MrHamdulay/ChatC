#include "message.h"
#Include "string.h"

void message_partial_init(message_partial *mp) {
    mp->bufferSize = 1024;
    mp->buffer = malloc(1024*sizeof(char));
    mp->bufferPos = 0;
    mp->len = 0;
}

//clear buffer for next message read
void message_partial_clear(message_partial *mp) {
    mp->bufferPos = 0;
    //XXX: should we clear the buffer if it's too big?
}

void message_partial_get_length(message_partial *mp) {
    if(mp->len == 0) {
        //make sure we have the full length message (rare that we wouldn't but still)
        int nullIndex = 0;
        for(int i=0; i<mp->bufferPos; i++) {
            if(mp->buffer[i] == 0) {
                nullIndex = i;
                break;
            }
        }
        if(nullIndex == 0)
            return;
        mp->len = atoi(mp->buffer);
    }
}

int message_partial_is_complete(message_partial *mp) {
    message_partial_get_length(mp);
    return mp->len == mp->bufferPos;
}

void message_partial_free(message_partial *mp) {
    free(mp->buffer);
}

void message_partial_parse_send_message(message_partial *mp, message *m, int index) {
    message_send_message *msm = (*message_send_message)malloc(sizeof(message_send_message));
    m->data = msm;

    msm->
}

void message_partial_parse_authenticate(message_partial *mp, message *m, int index) {
    message_authenticate *ma = (*message_authenticate)malloc(sizeof(message_authenticate));
    m->data = ma;
}

void message_partial_parse_dummy(message_partial *mp, message *m, int index) {
    m->data = NULL;
}

void message_partial_parse_get_roster(message_partial *mp, message *m, int index) {
    message_partial_parse_dummy(mp, m, index);
}


//maps command numbers to functors that will parse the message
void (*message_partial_parse_map[])(message_partial*, message*, int) = {
                        &message_partial_parse_dummy,
                        &message_partial_parse_send_message,
                        &message_partial_parse_authenticate,
                        &message_partial_parse_get_roster};

message* message_partial_parse(message_partial *mp) {
    message_partial_get_length(mp);
    if(!message_partial_is_complete(mp))
        return NULL;

    message *m = (message*)malloc(sizeof(message));

    int i =0;
    //get index of first 0
    while(i < mp->bufferPos && mp->buffer[i++]);
    //get command
    m->command = atoi(mp->buffer+i);
    //make sure it doesn't start on a 0
    i++;
    //find beginning of data
    while(i < mp->bufferPos && mp->buffer[i++]);

    if(m->command < sizeof(message_partial_parse_map)/sizeof(void *(message_partial*, message*, int)))
        *message_partial_parse_map[m->command](mp, m, i);
    else
        return NULL;

    return m;
}
