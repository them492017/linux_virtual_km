#include "network.h"

int create_socket() {
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

    if (bind(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        return -1;
    }

    return socket_fd;
}

int receive_key_event(struct key_event_packet* event, int socket_fd) {
    printf("Receiving key event!\n");
    // struct sockaddr_in addr = {0};
    // size_t addr_len = sizeof(addr);
    ssize_t nbytes = recvfrom(socket_fd, event, sizeof(struct key_event_packet), \
            0, NULL, NULL);

    if (nbytes < 0) {
        perror("Error when receiving key events");
        return 1;
    }

    // TODO: validate input is valid
    // TODO: validate incoming address is correct?
    printf("Received: %d\n", event->key);

    return 0;
}
