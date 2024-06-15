#include <linux/uinput.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

void emit(int fd, int type, int code, int val) {
    struct input_event ie = { 0 };

    ie.type = type;
    ie.code = code;
    ie.value = val;
    /* timestamp values below are ignored */
    ie.time.tv_sec = 0;
    ie.time.tv_usec = 0;

    if (write(fd, &ie, sizeof(ie)) < sizeof(ie)) {
        perror("Could not write full event to /dev/uinput");
    }
}

void emit_key_press(int fd, int val) {
    emit(fd, EV_KEY, val, 1);
    emit(fd, EV_SYN, SYN_REPORT, 0);
    emit(fd, EV_KEY, val, 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

int main(void) {
    struct uinput_setup usetup = { 0 };

    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (fd == -1) {
        perror("Could not open /dev/uinput");
        return 1;
    }

    ioctl(fd, UI_SET_EVBIT, EV_KEY);
    ioctl(fd, UI_SET_KEYBIT, KEY_SPACE);

    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234; /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
    strcpy(usetup.name, "Example device");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

    /* Key press, report the event, send key release, and report again */
    for (int i = 0; i < 10; i++) {
        emit_key_press(fd, KEY_SPACE);

        sleep(1);
    }

    /*
     * Give userspace some time to read the events before we destroy the
     * device with UI_DEV_DESTOY.
     */
    sleep(1);

    ioctl(fd, UI_DEV_DESTROY);
    close(fd);

    return 0;
}
