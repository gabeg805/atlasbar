#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef UTIL_H
#define UTIL_H

int get_gbar();
void kill_gbar();
void cleanup_child(int signal);
void widget_event(GtkWidget *holder, GtkWidget *widget, int timer, gboolean (*func)(gpointer));

#endif
