// -*-c++-*-
// **********************************************************************************
// 
// Name:    Statusbar
// Class:   <Statusbar>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The Atlas Statusbar container skeleton.
//              
// Notes: None.
// 
// **********************************************************************************


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
    
    // Container for the Atlas Statusbar widgets
    Gtk::Box    bar;
    
    // Set the desired widget onto the statusbar
    template <typename atlas_a>
    void attach(atlas_a& app, StatusWidget::Section section) {
        app.create();
        StatusWidget::attach(bar, app.widget, section);
    }
};

#endif
