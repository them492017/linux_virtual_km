#ifndef EVENT_H
#define EVENT_H

enum key_event_type {
    PRESS,
    RELEASE,
};

struct key_event {
    int key;
    enum key_event_type type;
};

struct pointer_event {
    double x, y; // TODO: rename / redefine struct
};

#endif
