#include "network.h"

int create_outgoing_socket() {
    int socket_fd = -1;
    struct sockaddr_in server_addr = {0};

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    if (inet_aton(SERVER_IP, &server_addr.sin_addr) == 0) {
        fprintf(stderr, "Invalid address\n");
        close(socket_fd);
        return -1;
    }

    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
            0) {
        perror("Bind failed");
        return -1;
    }

    return socket_fd;
}

struct sockaddr_in create_address(char *ip, int port) {
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_aton(ip, &server_addr.sin_addr) == 0) {
        fprintf(stderr, "Invalid address\n");
        return (struct sockaddr_in){0};
    }

    return server_addr;
}

int create_incoming_socket() {
    int socket_fd = -1;

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    return socket_fd;
}

// int receive_key_event(struct key_event *event, int socket_fd) {
//     printf("Receiving key event!\n");
//     // struct sockaddr_in addr = {0};
//     // size_t addr_len = sizeof(addr);
//     ssize_t nbytes =
//         recvfrom(socket_fd, event, sizeof(*event), 0, NULL, NULL);
//
//     if (nbytes < 0) {
//         perror("Error when receiving key events");
//         return 1;
//     }
//
//     // TODO: validate input is valid
//     // TODO: validate incoming address is correct?
//     printf("Received: %d\n", event->key);
//
//     return 0;
// }
//
// int receive_pointer_event(struct pointer_event *event, int socket_fd) {
//     printf("Receiving pointer event!\n");
//     // struct sockaddr_in addr = {0};
//     // size_t addr_len = sizeof(addr);
//     ssize_t nbytes =
//         recvfrom(socket_fd, event, sizeof(*event), 0, NULL, NULL);
//
//     if (nbytes < 0) {
//         perror("Error when receiving pointer events");
//         return 1;
//     }
//
//     // TODO: validate input is valid
//     // TODO: validate incoming address is correct?
//     printf("Received pointer event\n");
//
//     return 0;
// }

int receive_event(struct event_packet *packet, int socket_fd) {
    printf("Receiving event!\n");
    // struct sockaddr_in addr = {0};
    // size_t addr_len = sizeof(addr);
    ssize_t nbytes =
        recvfrom(socket_fd, packet, sizeof(*packet), 0, NULL, NULL);

    if (nbytes < 0) {
        perror("Error when receiving packet");
        return 1;
    }

    return 0;
}

// int send_key_event(struct key_event *event, struct sockaddr_in *addr, int socket_fd) {
//     printf("Sending key event!\n");
//     if (sendto(socket_fd, event, sizeof(*event), 0,
//                 (struct sockaddr *)addr, sizeof(*addr)) < 0) {
//         perror("Error when receiving key events");
//         return 1;
//     }
//
//     return 0;
// }
//
// int send_pointer_event(struct pointer_event *event, struct sockaddr_in *addr, int socket_fd) {
//     printf("Sending pointer event!\n");
//     if (sendto(socket_fd, event, sizeof(*event), 0,
//                 (struct sockaddr *)addr, sizeof(*addr)) < 0) {
//         perror("Error when receiving pointer events");
//         return 1;
//     }
//
//     return 0;
// }

int send_event(struct event_packet *packet, struct sockaddr_in *addr, int socket_fd) {
    printf("Sending event!\n");
    if (sendto(socket_fd, packet, sizeof(*packet), 0,
                (struct sockaddr *)addr, sizeof(*addr)) < 0) {
        perror("Error when sending event");
        return 1;
    }

    return 0;
}

#ifdef USE_X11

struct event_packet make_key_packet(XKeyEvent* event) {
    KeySym keysym;
    XLookupString(event, NULL, 0, &keysym, NULL);
    int key = keysym_to_uinput_keycode(keysym);
    return (struct event_packet) {
        .type = KEY,
        .event = {.key = (struct key_event) {
            .type = event->type,
            .key = key
        }},
    };
}

struct event_packet make_pointer_packet(XMotionEvent* event) {
    return (struct event_packet) {
        .type = POINTER,
        .event = {.pointer = (struct pointer_event) {
            .x = event->x,
            .y = event->y,
        }},
    };
}

#endif
