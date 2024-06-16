#include "server.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Correct usage: ./server.c {IP} {PORT}\n");
        return 1;
    }

    char* ip = argv[1];
    int port = atoi(argv[2]); // No error checking here (maybe rethink)

    int socket_fd = create_outgoing_socket();
    struct sockaddr_in addr = create_address(ip, port);
    int device_fd = create_keyboard_device();

    if (socket_fd == -1) {
        printf("Error when creating socket\n");
        return 1;
    }

    if (device_fd == -1) {
        printf("Error when creating device\n");
        return 1;
    }

    struct key_event_packet key_event = {0};

    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        exit(1);
    }

    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);

    // Create an InputOnly window
    Window input_only_window =
        XCreateWindow(display, root, 100, 100, 400, 300, 0, CopyFromParent,
                InputOnly, CopyFromParent, 0, NULL);

    // Select input events to listen for
    XSelectInput(display, input_only_window, KeyPressMask | ButtonPressMask);

    // Map the window (make it receive events)
    XMapWindow(display, input_only_window);

    // Event loop
    XEvent event;
    KeySym keysym;
    while (1) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            XLookupString(&event.xkey, NULL, 0, &keysym, NULL);
            key_event.key = keysym_to_uinput_keycode(keysym);
            send_key_event(&key_event, &addr, socket_fd);
            // printf("first keysym: %lu", XLookupKeysym(&event.xkey, 0));
        } else if (event.type == ButtonPress) {
            printf("Button pressed\n");
        }
    }

    // Destroy the window and close the display
    XDestroyWindow(display, input_only_window);
    XCloseDisplay(display);

    close_keyboard_device(device_fd);

    return 0;
}
