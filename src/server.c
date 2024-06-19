#include "server.h"

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Correct usage: ./server.c {IP} {PORT}\n");
        return 1;
    }

    char* ip = argv[1];
    int port = atoi(argv[2]); // TODO: No error checking here (maybe rethink)

    int socket_fd = create_outgoing_socket();
    struct sockaddr_in addr = create_address(ip, port);

    if (socket_fd == -1) {
        fprintf(stderr, "Error when creating socket\n");
        return 1;
    }

    Display *display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    int screen = DefaultScreen(display);
    Window root = RootWindow(display, screen);

    // Create an InputOnly window
    int attr_mask = CWEventMask | CWOverrideRedirect;
    XSetWindowAttributes attrs = {
        .event_mask = KeyPressMask | KeyReleaseMask \
                        | ButtonPressMask | ButtonReleaseMask | FocusChangeMask,
        .override_redirect = True,
    };

    Window input_only_window = \
        XCreateWindow(display, root, 100, 100, 400, 300, 0, CopyFromParent, \
                InputOnly, CopyFromParent, attr_mask, &attrs); // TODO: add error checking on these X calls

    // Map the window (make it receive events)
    XMapWindow(display, input_only_window); // TODO: add error checking

    if (XGrabKeyboard(display, input_only_window, True, GrabModeAsync, \
                GrabModeAsync, CurrentTime) != GrabSuccess) {
        fprintf(stderr, "Failed to grab keyboard\n");
        XCloseDisplay(display);
        return 1;
    }

    if (XGrabPointer(display, input_only_window, True, \
                ButtonPressMask | ButtonReleaseMask | PointerMotionMask, \
                GrabModeAsync, GrabModeAsync, None, None, CurrentTime) != GrabSuccess) {
        fprintf(stderr, "Failed to grab pointer\n");
        XCloseDisplay(display);
        return 1;
    }

    // Read config file
    struct linuxkm_config config = {0};
    parse_config(&config);

    // Start pointer thread
    pthread_t pointer_thread;
    struct pointer_thread_args arg = {
        .socket_fd = socket_fd,
        .addr = &addr,
    };
    pthread_create(&pointer_thread, NULL, pointer_thread_start, &arg);

    // Event loop
    XEvent event;
    struct event_packet packet = {0};
    while (1) {
        if (keybind_pressed(display, config.exit_key)) {
            printf("Closing program\n");
            break;
        }

        XNextEvent(display, &event);
        if (event.type == KeyPress || event.type == KeyRelease) {
            debug("Key pressed\n");
            packet = make_key_packet(&event.xkey);
            send_event(&packet, &addr, socket_fd);
        } else if (event.type == ButtonPress || event.type == ButtonRelease) {
            debug("Button pressed\n");
            packet = make_button_packet(&event.xbutton);
            send_event(&packet, &addr, socket_fd);
        }
    }

    // Stop pointer thread
    stop_pointer_thread();

    // Destroy the window and close the display
    XDestroyWindow(display, input_only_window);
    XCloseDisplay(display);

    pthread_join(pointer_thread, NULL);

    return 0;
}
