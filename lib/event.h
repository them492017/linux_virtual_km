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

struct point {
    int x;
    int y;
};

struct pointer_event {
    int x, y; // TODO: rename / redefine struct
};

#endif
