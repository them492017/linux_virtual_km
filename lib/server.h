#ifndef SERVER_H
#define SERVER_H

#include "network.h"
#include "device.h"
#include "pointer.h"
#include "debug.h"
#include "x11_util.h"
#include "config.h"

#ifdef USE_X11
#include <X11/Xutil.h>
#include <X11/extensions/XInput2.h>
#endif

#include <stdlib.h>
#include <pthread.h>

int main(int argc, char** argv);

#endif
