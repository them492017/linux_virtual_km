#include "client.h"

int main(void) {
    int socket_fd = create_socket();
    int device_fd = create_keyboard_device();
    struct key_event_packet event = {0};

    sleep(1);

    emit_key_press(device_fd, KEY_T);
    emit_key_press(device_fd, KEY_E);
    emit_key_press(device_fd, KEY_S);
    emit_key_press(device_fd, KEY_T);
    emit_key_press(device_fd, KEY_I);
    emit_key_press(device_fd, KEY_N);
    emit_key_press(device_fd, KEY_G);

    while (1) {
        if (receive_key_event(&event, socket_fd) == 0) {
            ; // do something
        }
    }

    close_keyboard_device(device_fd);

    return 0;
}
