// ============
// Header Guard
// ============

#ifndef STATUSBAR_H
#define STATUSBAR_H


// ========
// Includes
// ========

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class StatusBar : public Gtk::Window {
public:
    StatusBar();
    
    Gtk::Box      bar;
    
    std::string background;
    std::string foreground;
    
    enum Section { ALIGN_LEFT=1, ALIGN_CENTER, ALIGN_RIGHT };
};

#endif
