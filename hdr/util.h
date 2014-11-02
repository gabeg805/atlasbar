// Header guard
#ifndef UTIL_H
#define UTIL_H

// Includes
#include <gtk/gtk.h>

// Public functions
void setup_widget(GtkWidget *win, GtkWidget *widg, int pos[4]);
void file_write(char *file, char *opt, const char *fmt, ...);
char * file_read(char *file, int ln, int sz);
void kill_gbar();
void cleanup_child(int signal);
void widget_event(GtkWidget *holder, GtkWidget *widget, int timer, gboolean (*func)(gpointer));
void setup_window(GtkWidget *window, GtkWidget *bar);
void set_style();
void widget_mouse_enter(GtkWidget *win, GtkWidget *widget, int timer, gboolean (*func)(gpointer));

#endif
