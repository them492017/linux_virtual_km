#ifndef EVENT_H
#define EVENT_H

enum key_event_type {
    KEY_PRESS,
    KEY_RELEASE,
};

struct key_event {
    int key;
    enum key_event_type type;
};

struct pointer_event {
    double x;
    double y; // TODO: rename / redefine struct (should be int)
};

enum button_event_type {
    BUTTON_PRESS,
    BUTTON_RELEASE,
    WHEEL,
};

struct button_event {
    int button;
    enum button_event_type type;
};

#endif
