#include "client.h"

pthread_mutex_t pointer_batch_lock;
volatile struct pointer_event pointer_event_batch = {0};

void pointer_event_batch_insert(volatile struct pointer_event* batch, \
        pthread_mutex_t* lock, struct pointer_event event) {
    pthread_mutex_lock(lock);
    batch->x += event.x;
    batch->y += event.y;
    pthread_mutex_unlock(lock);
}

void* periodic_batch_flush(void* arg) {
    int* pointer_fd = arg;

    while (1) {
        if (pointer_event_batch.x != 0 || pointer_event_batch.y != 0) {
            pthread_mutex_lock(&pointer_batch_lock);
            emit_pointer_event(*pointer_fd, pointer_event_batch);
            pointer_event_batch.x = 0;
            pointer_event_batch.y = 0;
            pthread_mutex_unlock(&pointer_batch_lock);
        }
        usleep(POINTER_UPDATE_RATE); // maybe stop this from actively polling
    }

    return NULL;
}

int main(void) {
    int socket_fd = create_incoming_socket();
    int keyboard_fd = create_keyboard_device();
    int pointer_fd = create_pointer_device();

    if (socket_fd == -1) {
        fprintf(stderr, "Error when creating socket\n");
        return 1;
    }

    if (keyboard_fd == -1) {
        fprintf(stderr, "Error when creating device\n");
        return 1;
    }

    // create thread to manage tcp connection
    pthread_t tcp_thread;
    pthread_create(&tcp_thread, NULL, client_tcp_thread, NULL);

    struct event_packet packet = {0};

    sleep(1);

    // initialise mutex and thread
    pthread_t pointer_thread;
    pthread_mutex_init(&pointer_batch_lock, NULL);
    pthread_create(&pointer_thread, NULL, periodic_batch_flush, &pointer_fd);

    printf("Starting event loop\n");

    while (1) {
        if (receive_event(&packet, socket_fd) == 0) {
            switch (packet.type) {
                case KEY:
                    emit_key_event(keyboard_fd, packet.event.key); // TODO: maybe check key is valid first
                    break;
                case POINTER:
                    pointer_event_batch_insert(&pointer_event_batch, \
                            &pointer_batch_lock, packet.event.pointer);
                    break;
                case BUTTON:
                    emit_button_event(keyboard_fd, packet.event.button);
                    break;
            }
        }
        // if (!server_active()) {
        //     release_all(keyboard_fd);
        // }
    }

    close_device(keyboard_fd);
    close_device(pointer_fd);

    return 0;
}
