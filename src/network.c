#include "network.h"

int create_outgoing_socket() {
    int socket_fd = -1;

    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    return socket_fd;
}

int create_incoming_socket() {
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

int receive_event(struct event_packet *packet, int socket_fd) {
    // printf("Receiving event!\n");
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

int send_event(struct event_packet *packet, struct sockaddr_in *addr, int socket_fd) {
    // printf("Sending event!\n");
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
    enum key_event_type type;

    if (event->type == KeyPress) {
        type = KEY_PRESS;
    } else {
        type = KEY_RELEASE;
    }

    return (struct event_packet) {
        .type = KEY,
            .event = {.key = (struct key_event) {
                .type = type,
                .key = key
            }},
    };
}

struct event_packet make_pointer_packet(double dx, double dy) {
    return (struct event_packet) {
        .type = POINTER,
            .event = {.pointer = (struct pointer_event) {
                .x = dx,
                .y = dy,
            }},
    };
}

struct event_packet make_button_packet(XButtonEvent* event) {
    int button = button_to_uinput_keycode(event->button);
    enum button_event_type type;

    if (button == KEY_SCROLLUP || button == KEY_SCROLLDOWN) {
        type = WHEEL;
    } else if (event->type == ButtonPress) {
        type = BUTTON_PRESS;
    } else {
        type = BUTTON_RELEASE;
    }

    return (struct event_packet) {
        .type = BUTTON,
            .event = {.button = (struct button_event) {
                .type = type,
                .button = button
            }},
    };
}

#endif
