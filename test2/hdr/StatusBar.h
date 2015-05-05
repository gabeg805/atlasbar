// ============
// Header Guard
// ============

#ifndef STATUSBAR_H
#define STATUSBAR_H


// ========
// Includes
// ========

#include <gtkmm.h>


// =======
// Classes
// =======

class StatusBar : public Gtk::Window {
 public:
    StatusBar();
    
    Gtk::Box      bar;
    
    std::string background;
    std::string foreground;
    
    enum Section { LEFT=1, CENTER, RIGHT };
};

#endif
