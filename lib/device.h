#include <linux/uinput.h>

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define KEY_CODES { \
    KEY_SPACE, \
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
    -1 \
}

int create_keyboard_device();

void close_keyboard_device(int fd);

void emit(int fd, int type, int code, int val);

void emit_key_press(int fd, int key_val);
