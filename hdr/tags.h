#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef TAGS_H
#define TAGS_H

void display_tags(GtkWidget *bar, PangoAttrList *attrList, int screen);

#endif
