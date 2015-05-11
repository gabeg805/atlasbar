// -*-c++-*-

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

template <typename atlas_w>
class StatusSimple : public StatusWidget {
public:
    
    // Class variables
    atlas_w        *item;
    std::string    (*updateCall)();
    
    // Constructors
    StatusSimple(std::string str) { 
        item = Gtk::manage( new atlas_w(str) ); 
    }
    
    StatusSimple(std::string str, std::string font, int size) { 
        item = Gtk::manage( new Gtk::Label(str) ); 
        StatusWidget::font(item, font, size); 
    }
    
    // Application
    void           call(std::string (*func)()) { updateCall = func; }
    void           update(std::string (*func)(), int time);
    bool           set(atlas_w *orig);
    bool           set();
    
    // Style
    void           padding(int x, int y) { StatusWidget::padding(this, x, y); }
};



// ///////////////////////
// ///// APPLICATION /////
// ///////////////////////

// Try and see if you can store <int, int, int> in a variable
template <typename atlas_w>
inline void StatusSimple<atlas_w>::update(std::string (*func)(), int time) {
    typedef bool (StatusSimple::*statinfo)(atlas_w*);
    call(func); // updateCall = func;
    
    sigc::slot<bool, atlas_w*> pack = 
        sigc::mem_fun(*this, static_cast<statinfo>(&StatusSimple::set));
    Glib::signal_timeout().connect_seconds(sigc::bind<atlas_w*>(pack, item), time);
}



// Default icon/label setter 
template <typename atlas_w>
inline bool StatusSimple<atlas_w>::set(atlas_w *orig) {
    return true;
}

// Set the icon for the statusbar image
template <>
inline bool StatusSimple<Gtk::Image>::set(Gtk::Image *orig) {
    item->set( updateCall() ); 
    return true;
}

// Set the label for the statusbar label
template <>
inline bool StatusSimple<Gtk::Label>::set(Gtk::Label *orig) {
    item->set_text( updateCall() ); 
    return true;
}

// Set the icon/label
template <typename atlas_w>
inline bool StatusSimple<atlas_w>::set() {
    set(item); 
    return true;
}

#endif
