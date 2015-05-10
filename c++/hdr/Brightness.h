// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Brightness {
public:
    static std::string               icon();
    void                             create();
    
    static StatusSimple<Gtk::Image>    *widget;
};


// Declares
extern Brightness *brightness;

#endif
