#include "client.h"

int main(void) {
    int socket_fd = create_incoming_socket();
    int keyboard_fd = create_keyboard_device();
    int pointer_fd = create_pointer_device();

    if (socket_fd == -1) {
        printf("Error when creating socket\n");
        return 1;
    }

    if (keyboard_fd == -1) {
        printf("Error when creating device\n");
        return 1;
    }

    struct event_packet packet = {0};

    sleep(1);

    printf("Starting event loop\n");

    while (1) {
        if (receive_event(&packet, socket_fd) == 0) {
            switch (packet.type) {
                case KEY:
                    emit_key_event(keyboard_fd, packet.event.key); // TODO: maybe check key is valid first
                    break;
                case POINTER:
                    emit_pointer_event(pointer_fd, packet.event.pointer);
                    break;
            }
        }
    }

    close_device(keyboard_fd);
    close_device(pointer_fd);

    return 0;
}
