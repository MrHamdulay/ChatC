#ifndef __ASYNC_H
#define __ASYNC_H
struct ev_loop {
};
typedef struct ev_loop ev_loop;


void start_ev_loop(ev_loop *loop);
#endif
