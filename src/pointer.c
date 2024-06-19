#include "pointer.h"

#ifdef USE_X11

volatile int pointer_loop_stopped = 0;

void stop_pointer_thread() {
    pointer_loop_stopped = 1;
}

int initialise_xinput(Display* dpy) {
    int xi_opcode, xi_event, xi_error;
    // Initialize the XInput2 extension
    if (!XQueryExtension(dpy, "XInputExtension", &xi_opcode, &xi_event, &xi_error)) {
        fprintf(stderr, "X Input extension not available\n");
        return 1;
    }

    // Check for XInput2 version
    int major = 2, minor = 0;
    if (XIQueryVersion(dpy, &major, &minor) != Success) {
        fprintf(stderr, "XInput2 not supported. Version %d.%d\n", major, minor);
        return 1;
    }

    Window root = DefaultRootWindow(dpy);
    select_xinput2_events(dpy, root);

    return xi_opcode;
}

void select_xinput2_events(Display* dpy, Window win) {
    // Select for raw motion events on the root window
    XIEventMask evmask;
    unsigned char mask[(XI_LASTEVENT + 7)/8] = { 0 };
    evmask.deviceid = XIAllDevices;
    evmask.mask_len = sizeof(mask);
    evmask.mask = mask;
    XISetMask(mask, XI_RawMotion);

    XISelectEvents(dpy, win, &evmask, 1);
    XFlush(dpy);
}

void* pointer_thread_start(void* arg) {
    struct pointer_thread_args* args = arg;
    int socket_fd = args->socket_fd;
    struct sockaddr_in* addr = args->addr;

    Display* dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return NULL;
    }

    int xi_opcode = initialise_xinput(dpy);

    XEvent event;
    struct event_packet packet;
    while (!pointer_loop_stopped) {
        XNextEvent(dpy, &event);
        XGenericEventCookie* cookie = &event.xcookie;

        if (cookie->type == GenericEvent && cookie->extension == xi_opcode \
                && XGetEventData(dpy, cookie)) {
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
        XFreeEventData(dpy, cookie);
    }

    return NULL;
}

#endif
