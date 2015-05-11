// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef STATUSBAR_H
#define STATUSBAR_H


// ========
// Includes
// ========

#include "../hdr/StatusWidget.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Statusbar : public Gtk::Window {
public:
    Statusbar();
    
    Gtk::Box      *bar;
        
    // Set the desired widget onto the statusbar
    template <typename atlas_a>
    void attach(atlas_a *app, StatusWidget::Section section) {
        app->create();
        StatusWidget::attach(bar, app->widget, section);
    }
};

#endif