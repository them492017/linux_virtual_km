#include "device.h"

int create_keyboard_device() {
    struct uinput_setup usetup = { 0 };

    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (fd == -1) {
        perror("Could not open /dev/uinput");
        return -1;
    }

    if (ioctl(fd, UI_SET_EVBIT, EV_KEY) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }
    if (ioctl(fd, UI_SET_EVBIT, EV_REL) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }

    const int key_codes[] = KEY_CODES;
    int i = 0;

    while (key_codes[i] != -1) {
        if (ioctl(fd, UI_SET_KEYBIT, key_codes[i]) == -1) {
            perror("Error in ioctl");
            close(fd);
            return -1;
        }
        i++;
    }

    if (ioctl(fd, UI_SET_RELBIT, REL_WHEEL) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }

    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1; /* sample vendor */
    usetup.id.product = 0x1; /* sample product */
    strcpy(usetup.name, "Keyboard virtual device");

    if (ioctl(fd, UI_DEV_SETUP, &usetup) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }
    if (ioctl(fd, UI_DEV_CREATE) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }

    return fd;
}

int create_pointer_device() {
    struct uinput_setup usetup = { 0 };

    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (fd == -1) {
        perror("Could not open /dev/uinput");
        return -1;
    }

    if (ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0) {
        perror("Error in ioctl");
    }

    if (ioctl(fd, UI_SET_KEYBIT, BTN_LEFT) < 0) {
        perror("Error in ioctl");
    }

    if (ioctl(fd, UI_SET_EVBIT, EV_REL) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }
    if (ioctl(fd, UI_SET_EVBIT, EV_SYN) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }
    if (ioctl(fd, UI_SET_RELBIT, REL_X) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }
    if (ioctl(fd, UI_SET_RELBIT, REL_Y) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }

    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1; /* sample vendor */
    usetup.id.product = 0x1; /* sample product */
    strcpy(usetup.name, "Mouse virtual device");

    if (ioctl(fd, UI_DEV_SETUP, &usetup) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }
    if (ioctl(fd, UI_DEV_CREATE) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }

    return fd;
}
void close_device(int fd) {
    if (ioctl(fd, UI_DEV_DESTROY) == -1) {
        perror("Error in ioctl");
    }

    close(fd);
}

void emit(int fd, int type, int code, int val) {
    struct input_event ie = { 0 };

    ie.type = type;
    ie.code = code;
    ie.value = val;

    if (write(fd, &ie, sizeof(ie)) < sizeof(ie)) {
        perror("Could not write full event to /dev/uinput");
    }
}

void emit_key_event(int fd, struct key_event event) {
    debugf("Emitting type/key: %d/%d\n", event.type, event.key);
    switch (event.type) {
        case KEY_PRESS:
            emit(fd, EV_KEY, event.key, 1);
            emit(fd, EV_SYN, SYN_REPORT, 0);
            break;
        case KEY_RELEASE:
            emit(fd, EV_KEY, event.key, 0);
            emit(fd, EV_SYN, SYN_REPORT, 0);
            break;
    };
}

void emit_pointer_event(int fd, struct pointer_event event) {
    debugf("Emitting pointer event: (%f, %f)\n", event.x, event.y);
    emit(fd, EV_REL, REL_X, MOUSE_SENS * event.x);
    emit(fd, EV_REL, REL_Y, MOUSE_SENS * event.y);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

void emit_button_event(int fd, struct button_event event) {
    debugf("Emitting button event (type/buton): %d/%d\n", event.type, event.button);
    switch (event.type) {
        case BUTTON_PRESS:
            emit(fd, EV_KEY, event.button, 1);
            emit(fd, EV_SYN, SYN_REPORT, 0);
            break;
        case BUTTON_RELEASE:
            emit(fd, EV_KEY, event.button, 0);
            emit(fd, EV_SYN, SYN_REPORT, 0);
            break;
        case WHEEL:
            if (event.button == KEY_SCROLLUP) {
                emit(fd, EV_REL, REL_WHEEL, 1);
                emit(fd, EV_SYN, SYN_REPORT, 0);
            }
            if (event.button == KEY_SCROLLDOWN) {
                emit(fd, EV_REL, REL_WHEEL, -1);
                emit(fd, EV_SYN, SYN_REPORT, 0);
            }
            break;
    }
}
