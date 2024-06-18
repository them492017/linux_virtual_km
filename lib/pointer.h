#ifndef POINTER_H
#define POINTER_H

#include "network.h"

#include <stdio.h>

extern volatile int pointer_loop_stopped;

#ifdef USE_X11

#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>

struct pointer_thread_args {
    struct sockaddr_in* addr;
    int socket_fd;
};

int initialise_xinput(Display* dpy);

void select_xinput2_events(Display* dpy, Window win);

int pointer_event_loop(Display* display, int xi_opcode);

void* pointer_thread_start(void* arg);

#endif

#endif /* ifndef POINTER_H */
