// Header guard
#ifndef STATUSBAR_H
#define STATUSBAR_H

// Includes
#include <gtk/gtk.h>
#include <string>

// =======
// Classes
// =======

/* gboolean      set_icon(gpointer eventbox, std::string (*get_icon)()); */

class Statusbar {
 public:
    void          init();
    int           get_percent(std::string cmd);
    
    GtkWidget     *win;
    GtkWidget     *bar;
    PangoAttrList *attr;
    
    // Left = -1; Middle = 0; Right = 1;
    
    class Image {
    public:
        void        init(std::string (*func)());
        gboolean    set(gpointer data);
        GCallback   seta();
        std::string (*get_icon)();
        void        setters(GtkWidget *bar, int section, int timer);
        
        GtkWidget   *img;
        GtkWidget   *event;
    };
};

    
    

extern Statusbar Atlas;

#endif
