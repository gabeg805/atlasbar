#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

#ifndef GBAR_H
#define GBAR_H

void gbar(int screen);

#endif
