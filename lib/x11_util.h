#ifndef X11_UTIL_H
#define X11_UTIL_H

#ifdef USE_X11

#include <linux/uinput.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

int keysym_to_uinput_keycode(KeySym keysym);

int button_to_uinput_keycode(unsigned int button);

#endif

#endif
