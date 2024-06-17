#ifndef NETWORK_H
#define NETWORK_H

#define _POSIX_SOURCE
#define _DEFAULT_SOURCE

#include "event.h"

#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>

#ifdef USE_X11

#include "x11_util.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif

#define SERVER_IP "0.0.0.0"
#define SERVER_PORT 7000

enum event_type {
    KEY,
    POINTER,
};

union event {
    struct key_event key;
    struct pointer_event pointer;
};

struct event_packet {
    enum event_type type;
    union event event;
};

int create_outgoing_socket();

int create_incoming_socket();

struct sockaddr_in create_address(char* ip, int port);

// int receive_key_event(struct key_event* event, int socket_fd);
// int receive_pointer_event(struct pointer_event* event, int socket_fd);
// int send_key_event(struct key_event *event, struct sockaddr_in *addr, int socket_fd);
// int send_pointer_event(struct pointer_event *event, struct sockaddr_in *addr, int socket_fd);

int receive_event(struct event_packet *packet, int socket_fd);

int send_event(struct event_packet *packet, struct sockaddr_in *addr, int socket_fd);

#ifdef USE_X11

struct event_packet make_key_packet(XKeyEvent* event);

struct event_packet make_pointer_packet(XMotionEvent* event);

#endif

#endif /* ifndef NETWORK_H */
