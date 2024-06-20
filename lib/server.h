#ifndef SERVER_H
#define SERVER_H

#include "network.h"
#include "device.h"
#include "debug.h"
#include "x11_util.h"
#include "config.h"

#ifdef USE_X11
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#endif

#include <stdlib.h>
#include <pthread.h>

int initialise_xinput(Display* display);

void select_xinput2_events(Display* display, Window win);

int main(int argc, char** argv);

#endif
