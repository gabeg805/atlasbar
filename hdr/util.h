// Header guard
#ifndef UTIL_H
#define UTIL_H

// Includes
#include <gtk/gtk.h>

// Public functions
void cleanup_child(int signal);
void kill_gbar();
void set_style();
void setup_widget(GtkWidget *win, GtkWidget *widg, int pos[4]);
void widget_mouse_enter(GtkWidget *win, GtkWidget *widget, int timer, gboolean (*func)(gpointer));
void widget_updater(int sig);

#endif
