#ifndef __USER_H
#define __USER_H
struct user {
    //unique user id
    int uid;

    //unix timestamp of last user activity
    int last_online;
    //0 if not online on any node
    int node;
};
typedef struct user user;

#endif
