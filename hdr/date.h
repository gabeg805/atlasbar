#include <gtk/gtk.h>

#ifndef DATE_H
#define DATE_H

gboolean set_date_label(gpointer data);
void display_date(GtkWidget *bar, PangoAttrList *attrList);

#endif
