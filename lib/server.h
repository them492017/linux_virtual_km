#ifndef SERVER_H
#define SERVER_H

#include "network.h"
#include "device.h"
#include "x11_util.h"

#ifdef USE_X11
#include <X11/Xutil.h>
#endif

#include <stdlib.h>

int main(int argc, char** argv);

#endif
