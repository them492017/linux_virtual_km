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

    if (socket_fd == -1) {
        printf("Error when creating socket\n");
        return 1;
    }

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
    XSelectInput(display, input_only_window, KeyPressMask | KeyReleaseMask | PointerMotionMask | ButtonPressMask);

    // Map the window (make it receive events)
    XMapWindow(display, input_only_window);

    // Event loop
    XEvent event;
    struct event_packet packet = {0};
    while (1) {
        XNextEvent(display, &event);
        if (event.type == KeyPress) {
            packet = make_key_packet(&event.xkey);
            send_event(&packet, &addr, socket_fd);
        } else if (event.type == MotionNotify) {
            packet = make_pointer_packet(&event.xmotion);
            send_event(&packet, &addr, socket_fd);
        } else if (event.type == ButtonPress) {
            printf("Mouse button pressed\n");
        }
    }

    // Destroy the window and close the display
    XDestroyWindow(display, input_only_window);
    XCloseDisplay(display);

    return 0;
}
