#include "x11_util.h"

#ifdef USE_X11

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

        case XK_A: return KEY_A;
        case XK_B: return KEY_B;
        case XK_C: return KEY_C;
        case XK_D: return KEY_D;
        case XK_E: return KEY_E;
        case XK_F: return KEY_F;
        case XK_G: return KEY_G;
        case XK_H: return KEY_H;
        case XK_I: return KEY_I;
        case XK_J: return KEY_J;
        case XK_K: return KEY_K;
        case XK_L: return KEY_L;
        case XK_M: return KEY_M;
        case XK_N: return KEY_N;
        case XK_O: return KEY_O;
        case XK_P: return KEY_P;
        case XK_Q: return KEY_Q;
        case XK_R: return KEY_R;
        case XK_S: return KEY_S;
        case XK_T: return KEY_T;
        case XK_U: return KEY_U;
        case XK_V: return KEY_V;
        case XK_W: return KEY_W;
        case XK_X: return KEY_X;
        case XK_Y: return KEY_Y;
        case XK_Z: return KEY_Z;

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

        case XK_exclam: return KEY_1;
        case XK_at: return KEY_2;
        case XK_numbersign: return KEY_3;
        case XK_dollar: return KEY_4;
        case XK_percent: return KEY_5;
        case XK_asciicircum: return KEY_6;
        case XK_ampersand: return KEY_7;
        case XK_asterisk: return KEY_8;
        case XK_parenleft: return KEY_9;
        case XK_parenright: return KEY_0;

        case XK_underscore: return KEY_MINUS;
        case XK_plus: return KEY_EQUAL;
        case XK_braceleft: return KEY_LEFTBRACE;
        case XK_braceright: return KEY_RIGHTBRACE;
        case XK_bar: return KEY_BACKSLASH;
        case XK_colon: return KEY_SEMICOLON;
        case XK_quotedbl: return KEY_APOSTROPHE;
        case XK_less: return KEY_COMMA;
        case XK_greater: return KEY_DOT;
        case XK_question: return KEY_SLASH;

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

        default: 
            debugf("Unknown keysym: %lu\n", keysym);
            return -1; // Unknown keysym
    }
}

int button_to_uinput_keycode(unsigned int button) {
    switch (button) {
        case Button1: return BTN_LEFT;
        case Button2: return BTN_MIDDLE;
        case Button3: return BTN_RIGHT;
        case Button4: return KEY_SCROLLUP;
        case Button5: return KEY_SCROLLDOWN;
        default: return -1;
    }
}

int key_is_down(Display* dpy, char* str) {
    KeySym keysym = XStringToKeysym(str);
    int keycode = XKeysymToKeycode(dpy, keysym);

    int target_byte = keycode / 8;
    int target_bit = keycode % 8;
    int target_mask = 1 << target_bit;

    char keys[32] = {0};
    XQueryKeymap(dpy, keys);

    return keys[target_byte] & target_mask;
}

int keybind_pressed(Display* dpy, struct keybind keybind) {
    if (keybind.meta && !key_is_down(dpy, "Super_L") && !key_is_down(dpy, "Super_R")) {
        return 0;
    }
    if (keybind.control && !key_is_down(dpy, "Control_L") && !key_is_down(dpy, "Control_R")) {
        return 0;
    }
    if (keybind.alt && !key_is_down(dpy, "Alt_L") && !key_is_down(dpy, "Alt_R")) {
        return 0;
    }
    if (keybind.shift && !key_is_down(dpy, "Shift_L") && !key_is_down(dpy, "Shift_R")) {
        return 0;
    }
    if (keybind.key && !key_is_down(dpy, (char[2]){keybind.key, 0})) {
        return 0;
    }

    return 1;
}

#endif
