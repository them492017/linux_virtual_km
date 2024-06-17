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

    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234; /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
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

    if (ioctl(fd, UI_SET_EVBIT, EV_ABS) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }
    if (ioctl(fd, UI_SET_EVBIT, ABS_X) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }
    if (ioctl(fd, UI_SET_EVBIT, ABS_Y) == -1) {
        perror("Error in ioctl");
        close(fd);
        return -1;
    }

    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234; /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
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
    switch (event.type) {
        case PRESS:
            emit(fd, EV_KEY, event.key, 1);
            emit(fd, EV_SYN, SYN_REPORT, 0);
            break;
        case RELEASE:
            emit(fd, EV_KEY, event.key, 0);
            emit(fd, EV_SYN, SYN_REPORT, 0);
            break;
    };
}

void emit_pointer_event(int fd, struct pointer_event event) {
    emit(fd, EV_ABS, ABS_X, event.x);
    emit(fd, EV_ABS, ABS_Y, event.y);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}
