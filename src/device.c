#include "device.h"

int keysym_to_uinput_keycode(KeySym keysym) {
    switch (keysym) {
        case XK_a: return KEY_A;
        case XK_b: return KEY_B;
        case XK_c: return KEY_C;
        case XK_d: return KEY_D;
        case XK_e: return KEY_E;
        case XK_f: return KEY_F;
        case XK_g: return KEY_G;
        case XK_h: return KEY_H;
        case XK_i: return KEY_I;
        case XK_j: return KEY_J;
        case XK_k: return KEY_K;
        case XK_l: return KEY_L;
        case XK_m: return KEY_M;
        case XK_n: return KEY_N;
        case XK_o: return KEY_O;
        case XK_p: return KEY_P;
        case XK_q: return KEY_Q;
        case XK_r: return KEY_R;
        case XK_s: return KEY_S;
        case XK_t: return KEY_T;
        case XK_u: return KEY_U;
        case XK_v: return KEY_V;
        case XK_w: return KEY_W;
        case XK_x: return KEY_X;
        case XK_y: return KEY_Y;
        case XK_z: return KEY_Z;

        case XK_1: return KEY_1;
        case XK_2: return KEY_2;
        case XK_3: return KEY_3;
        case XK_4: return KEY_4;
        case XK_5: return KEY_5;
        case XK_6: return KEY_6;
        case XK_7: return KEY_7;
        case XK_8: return KEY_8;
        case XK_9: return KEY_9;
        case XK_0: return KEY_0;

        case XK_Return: return KEY_ENTER;
        case XK_Escape: return KEY_ESC;
        case XK_BackSpace: return KEY_BACKSPACE;
        case XK_Tab: return KEY_TAB;
        case XK_space: return KEY_SPACE;
        case XK_minus: return KEY_MINUS;
        case XK_equal: return KEY_EQUAL;
        case XK_bracketleft: return KEY_LEFTBRACE;
        case XK_bracketright: return KEY_RIGHTBRACE;
        case XK_backslash: return KEY_BACKSLASH;
        case XK_semicolon: return KEY_SEMICOLON;
        case XK_apostrophe: return KEY_APOSTROPHE;
        case XK_grave: return KEY_GRAVE;
        case XK_comma: return KEY_COMMA;
        case XK_period: return KEY_DOT;
        case XK_slash: return KEY_SLASH;

        case XK_F1: return KEY_F1;
        case XK_F2: return KEY_F2;
        case XK_F3: return KEY_F3;
        case XK_F4: return KEY_F4;
        case XK_F5: return KEY_F5;
        case XK_F6: return KEY_F6;
        case XK_F7: return KEY_F7;
        case XK_F8: return KEY_F8;
        case XK_F9: return KEY_F9;
        case XK_F10: return KEY_F10;
        case XK_F11: return KEY_F11;
        case XK_F12: return KEY_F12;

        case XK_Shift_L: return KEY_LEFTSHIFT;
        case XK_Shift_R: return KEY_RIGHTSHIFT;
        case XK_Control_L: return KEY_LEFTCTRL;
        case XK_Control_R: return KEY_RIGHTCTRL;
        case XK_Alt_L: return KEY_LEFTALT;
        case XK_Alt_R: return KEY_RIGHTALT;
        case XK_Super_L: return KEY_LEFTMETA;
        case XK_Super_R: return KEY_RIGHTMETA;

        case XK_Caps_Lock: return KEY_CAPSLOCK;
        case XK_Num_Lock: return KEY_NUMLOCK;
        case XK_Scroll_Lock: return KEY_SCROLLLOCK;

        case XK_Insert: return KEY_INSERT;
        case XK_Delete: return KEY_DELETE;
        case XK_Home: return KEY_HOME;
        case XK_End: return KEY_END;
        case XK_Page_Up: return KEY_PAGEUP;
        case XK_Page_Down: return KEY_PAGEDOWN;

        case XK_Left: return KEY_LEFT;
        case XK_Up: return KEY_UP;
        case XK_Right: return KEY_RIGHT;
        case XK_Down: return KEY_DOWN;

        case XK_KP_0: return KEY_KP0;
        case XK_KP_1: return KEY_KP1;
        case XK_KP_2: return KEY_KP2;
        case XK_KP_3: return KEY_KP3;
        case XK_KP_4: return KEY_KP4;
        case XK_KP_5: return KEY_KP5;
        case XK_KP_6: return KEY_KP6;
        case XK_KP_7: return KEY_KP7;
        case XK_KP_8: return KEY_KP8;
        case XK_KP_9: return KEY_KP9;

        case XK_KP_Decimal: return KEY_KPDOT;
        case XK_KP_Divide: return KEY_KPSLASH;
        case XK_KP_Multiply: return KEY_KPASTERISK;
        case XK_KP_Subtract: return KEY_KPMINUS;
        case XK_KP_Add: return KEY_KPPLUS;
        case XK_KP_Enter: return KEY_KPENTER;
        case XK_KP_Equal: return KEY_KPEQUAL;

        default: return -1;  // Unknown keysym
    }
}

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

void close_keyboard_device(int fd) {
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

void emit_key_press(int fd, int key_val) {
    emit(fd, EV_KEY, key_val, 1);
    emit(fd, EV_SYN, SYN_REPORT, 0);
    emit(fd, EV_KEY, key_val, 0);
    emit(fd, EV_SYN, SYN_REPORT, 0);
}

// int main(void) {
//     int fd = create_keyboard_device();
//
//     if (fd == -1) {
//         printf("Closing program due to fatal error\n");
//         return 1;
//     }
//
//     // Wait for device to be created?
//     sleep(1);
//
//     // Emit key presses
//     for (int i = 0; i < 10; i++) {
//         emit_key_press(fd, KEY_SPACE);
//         usleep(10000); // add slight delay between keypresses for now
//     }
//
//     // Wait for events to be read
//     sleep(1);
//
//     close_keyboard_device(fd);
//
//     return 0;
// }
