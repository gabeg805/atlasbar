// -*-c++-*-
// **********************************************************************************
// 
// Name:    StatusSimple.h
// Class:   <StatusSimple>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The tools to contruct a simple widget (Image/Label) and its 
//              container.
//              
// Notes: Works well with Image and Label, try and generalize to other types.
//        Try and wrap the StatusWidget functions into this.
// 
// **********************************************************************************


// ============
// Header Guard
// ============

#ifndef STATUSITEM_H
#define STATUSITEM_H


// ========
// Includes
// ========

#include "../hdr/StatusWidget.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class StatusSimple {
public:
    
    // Class variables
    // std::unique_ptr<Gtk::Widget>    stuff;
    Gtk::Widget*    item;
    std::string     (*updateCall)();
    
    
    // Initialize the statusbar widget container
    template <typename atlas_w>
    void init(std::string str) { 
        item = Gtk::manage( new atlas_w(str) ); 
    }
    
    
    
    // Initialize the statusbar widget container
    template <typename atlas_w>
    void init(std::string str, int x, int y) { 
        item = Gtk::manage( new atlas_w(str) ); 
        StatusWidget::padding((atlas_w*)item, x, y); 
    }
    
    
    
    // Initialize the statusbar label widget with the given font attributes
    void init(std::string str, std::string font, int size) { 
        item = Gtk::manage( new Gtk::Label(str) ); 
        StatusWidget::font((Gtk::Label *)item, font, size); 
    }
    
    
    
    // Describe the function to call periodically with update
    void call(std::string (*func)()) { 
        updateCall = func;
    }
    
    
    
    // Call the described function periodically
    template <typename atlas_w>
    void update(std::string (*func)(), int time) {
        typedef bool (StatusSimple::*statinfo)(atlas_w*);
        call(func);
        
        sigc::slot<bool, atlas_w*> pack = 
            sigc::mem_fun(*this, static_cast<statinfo>(&StatusSimple::set));
        Glib::signal_timeout().connect_seconds(sigc::bind<atlas_w*>(pack, (atlas_w*)item), time);
    }
    
    
    
    // Set the icon for a statusbar image widget
    bool set(Gtk::Image *orig) {
        orig->set( updateCall() ); 
        return true;
    }
    
    
    
    // Set the label for the statusbar label widget
    bool set(Gtk::Label *orig) {
        orig->set_text( updateCall() ); 
        return true;
    }
    
    
    
    // Set the widget icon/label
    template <typename atlas_w>
    bool set() {
        set((atlas_w*)item); 
        return true;
    }
    
    
    
    // Wrapper for the widget padding
    template <typename atlas_w>
    void padding(int x, int y) { 
        StatusWidget::padding((atlas_w*)item, x, y); 
    }
};

#endif
