#ifndef __USER_H
#define __USER_H
#include "user.h"

struct room {
    llist users; //list of users 
    int created; //creation date
    user owner; //at the moment we only have one creator
};

struct room_user {
    user *user; //not all users are necessarily in the same room 

};
???
