// ============
// Header Guard
// ============

#ifndef BATTERY_H
#define BATTERY_H


// ========
// Includes
// ========

#include "../hdr/StatusItem.hpp"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Battery {
 public:
    static std::string               icon();
    void                             display(Gtk::Box *bar);
    
    static StatusItem<Gtk::Image>    *widget;
};


// Declares
extern Battery *battery;

#endif
