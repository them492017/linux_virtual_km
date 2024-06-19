#ifndef X11_UTIL_H
#define X11_UTIL_H

#ifdef USE_X11

#include "config.h"
#include "debug.h"

#include <linux/uinput.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

int keysym_to_uinput_keycode(KeySym keysym);

int button_to_uinput_keycode(unsigned int button);

int key_is_down(Display* dpy, char* str);

int keybind_pressed(Display* dpy, struct keybind keybind);

#endif

#endif
