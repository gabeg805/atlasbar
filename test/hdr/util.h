// Header guard
#ifndef UTIL_H
#define UTIL_H

// Includes
#include <gtk/gtk.h>

// Declarations
struct app {
    GtkWidget *win;
    GtkWidget *holder;
};

extern PangoAttrList *attrList;
extern struct app App;

// Public functions
void app_setup();

void set_style();
void widget_mouse_enter(GtkWidget *win, GtkWidget *widget, int timer, gboolean (*func)(gpointer));
void widget_mouse_entera(GtkWidget *event, GtkWidget *win, GtkWidget *widget, int timer, gboolean (*func)(gpointer));
void widget_updater(int sig);
int get_percent(char *cmd);

#endif
