#ifndef DEVICE_H
#define DEVICE_H

#include "event.h"

#include <linux/uinput.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define KEY_CODES { \
    KEY_A, \
    KEY_B, \
    KEY_C, \
    KEY_D, \
    KEY_E, \
    KEY_F, \
    KEY_G, \
    KEY_H, \
    KEY_I, \
    KEY_J, \
    KEY_K, \
    KEY_L, \
    KEY_M, \
    KEY_N, \
    KEY_O, \
    KEY_P, \
    KEY_Q, \
    KEY_R, \
    KEY_S, \
    KEY_T, \
    KEY_U, \
    KEY_V, \
    KEY_W, \
    KEY_X, \
    KEY_Y, \
    KEY_Z, \
    KEY_1, \
    KEY_2, \
    KEY_3, \
    KEY_4, \
    KEY_5, \
    KEY_6, \
    KEY_7, \
    KEY_8, \
    KEY_9, \
    KEY_0, \
    KEY_ENTER, \
    KEY_ESC, \
    KEY_BACKSPACE, \
    KEY_TAB, \
    KEY_SPACE, \
    KEY_MINUS, \
    KEY_EQUAL, \
    KEY_LEFTBRACE, \
    KEY_RIGHTBRACE, \
    KEY_BACKSLASH, \
    KEY_SEMICOLON, \
    KEY_APOSTROPHE, \
    KEY_GRAVE, \
    KEY_COMMA, \
    KEY_DOT, \
    KEY_SLASH, \
    KEY_F1, \
    KEY_F2, \
    KEY_F3, \
    KEY_F4, \
    KEY_F5, \
    KEY_F6, \
    KEY_F7, \
    KEY_F8, \
    KEY_F9, \
    KEY_F10, \
    KEY_F11, \
    KEY_F12, \
    KEY_LEFTSHIFT, \
    KEY_RIGHTSHIFT, \
    KEY_LEFTCTRL, \
    KEY_RIGHTCTRL, \
    KEY_LEFTALT, \
    KEY_RIGHTALT, \
    KEY_LEFTMETA, \
    KEY_RIGHTMETA, \
    KEY_CAPSLOCK, \
    KEY_NUMLOCK, \
    KEY_SCROLLLOCK, \
    KEY_INSERT, \
    KEY_DELETE, \
    KEY_HOME, \
    KEY_END, \
    KEY_PAGEUP, \
    KEY_PAGEDOWN, \
    KEY_LEFT, \
    KEY_UP, \
    KEY_RIGHT, \
    KEY_DOWN, \
    KEY_KP0, \
    KEY_KP1, \
    KEY_KP2, \
    KEY_KP3, \
    KEY_KP4, \
    KEY_KP5, \
    KEY_KP6, \
    KEY_KP7, \
    KEY_KP8, \
    KEY_KP9, \
    KEY_KPDOT, \
    KEY_KPSLASH, \
    KEY_KPASTERISK, \
    KEY_KPMINUS, \
    KEY_KPPLUS, \
    KEY_KPENTER, \
    KEY_KPEQUAL, \
    -1, \
}

#define MOUSE_SENS 1

int create_keyboard_device();

int create_pointer_device();

void close_device(int fd);

void emit(int fd, int type, int code, int val);

void emit_key_event(int fd, struct key_event event);

void emit_pointer_event(int fd, struct pointer_event event);

#endif
