// Header guard
#ifndef UTIL_H
#define UTIL_H

// Includes
#include <gtk/gtk.h>
#include <string>

// Public functions
void widget_mouse_enter(GtkWidget *win, GtkWidget *widget, int timer, gboolean (*func)(gpointer));
void widget_mouse_entera(GtkWidget *event, GtkWidget *widget, int timer, gboolean (*func)(gpointer));
void widget_updater(int sig);

#endif
