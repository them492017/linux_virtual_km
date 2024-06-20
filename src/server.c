#include "server.h"

int initialise_xinput(Display* display) {
    int xi_opcode, xi_event, xi_error;
    // Initialize the XInput2 extension
    if (!XQueryExtension(display, "XInputExtension", &xi_opcode, &xi_event, &xi_error)) {
        fprintf(stderr, "X Input extension not available\n");
        return 1;
    }

    // Check for XInput2 version
    int major = 2, minor = 0;
    if (XIQueryVersion(display, &major, &minor) != Success) {
        fprintf(stderr, "XInput2 not supported. Version %d.%d\n", major, minor);
        return 1;
    }

    Window root = DefaultRootWindow(display);
    select_xinput2_events(display, root);


    return xi_opcode;
}

void select_xinput2_events(Display* display, Window win) {
    // Select for raw motion events on the root window
    XIEventMask evmask;
    unsigned char mask[(XI_LASTEVENT + 7)/8] = { 0 };
    evmask.deviceid = XIAllDevices;
    evmask.mask_len = sizeof(mask);
    evmask.mask = mask;
    XISetMask(mask, XI_RawMotion);

    XISelectEvents(display, win, &evmask, 1);
    XFlush(display);
}

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

    int screen = DefaultScreen(display); // TODO: add error checking on these X calls
    Window root = RootWindow(display, screen);

    /* // Create an InputOnly window
    int attr_mask = CWEventMask | CWOverrideRedirect;
    XSetWindowAttributes attrs = {
        .event_mask = KeyPressMask | KeyReleaseMask \
                        | ButtonPressMask | ButtonReleaseMask | FocusChangeMask,
        .override_redirect = True,
    };

    Window input_only_window = \
        XCreateWindow(display, root, 100, 100, 400, 300, 0, CopyFromParent, \
                InputOnly, CopyFromParent, attr_mask, &attrs);

    // Map the window (make it receive events)
    XMapWindow(display, input_only_window); */

    // Initialise Xinput2
    int xi_opcode = initialise_xinput(display);

    if (XGrabKeyboard(display, root, True, GrabModeAsync, \
                GrabModeAsync, CurrentTime) != GrabSuccess) {
        fprintf(stderr, "Failed to grab keyboard\n");
        XCloseDisplay(display);
        return 1;
    }

    if (XGrabPointer(display, root, True, \
                ButtonPressMask | ButtonReleaseMask | PointerMotionMask, \
                GrabModeAsync, GrabModeAsync, None, \
                None, CurrentTime) != GrabSuccess) {
        fprintf(stderr, "Failed to grab pointer\n");
        XCloseDisplay(display);
        return 1;
    }

    // Read config file
    struct linuxkm_config config = {0};
    parse_config(&config);

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
        } else if (event.type == GenericEvent) {
            XGenericEventCookie* cookie = &event.xcookie;

            if (cookie->type == GenericEvent && cookie->extension == xi_opcode \
                    && XGetEventData(display, cookie)) {
                if (cookie->evtype == XI_RawMotion) {
                    XIRawEvent* raw_event = (XIRawEvent* )cookie->data;
                    unsigned char* val_mask = raw_event->valuators.mask;
                    double* raw_values = raw_event->raw_values;

                    // check raw_values are set correctly
                    if (XIMaskIsSet(val_mask, 0) && XIMaskIsSet(val_mask, 1)) {
                        double dx = raw_values[0];
                        double dy = raw_values[1];

                        packet = make_pointer_packet(dx, dy);
                        send_event(&packet, addr, socket_fd);
                        debugf("Relative motion: dx = %f, dy = %f\n", dx, dy);
                    }
                }
            }
            XFreeEventData(display, cookie);
        }
    }

    // Destroy the window and close the display
    // XDestroyWindow(display, input_only_window);
    XCloseDisplay(display);

    pthread_join(pointer_thread, NULL);

    // TODO: Need to release all keys that are being pressed on client

    return 0;
}
