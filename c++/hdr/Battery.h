// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef BATTERY_H
#define BATTERY_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Battery {
 public:
    static std::string               icon();
    void                             create();
    
    static StatusSimple<Gtk::Image>    *widget;
};


// Declares
extern Battery *battery;

#endif
