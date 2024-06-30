// should rename file or merge with network.c
#include "tcp.h"

int create_outgoing_socket() {
    int socket_fd = -1;
    struct sockaddr_in server_addr = {0};

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_TCP_PORT);
    if (inet_aton(SERVER_IP, &server_addr.sin_addr) == 0) {
        fprintf(stderr, "Invalid address\n");
        close(socket_fd);
        return -1;
    }

    return socket_fd;
}

int create_incoming_socket() {
    int socket_fd = -1;
    struct sockaddr_in server_addr = {0};

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_TCP_PORT);
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

    if (listen(socket_fd, 0) < 0) { // maybe change backlog value
        perror("Listen failed");
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

// have a shared variable CLIPBOARD_CONTENTS and overwrite it (use mutex for synchronisation)
// shutdown event occurs when socket disconnects

void* client_tcp_thread(void* arg) {
    int sock_fd = create_outgoing_socket();

    // connect(sock_fd, &addr, &addr_len);

    // read / write socket loop
}
