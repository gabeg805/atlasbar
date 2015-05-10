// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef WIFI_H
#define WIFI_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Wifi {
 public:
    static std::string               icon();
    void                             create();
    
    static StatusSimple<Gtk::Image>    *widget;
};


// Declares
extern Wifi *wifi;

#endif
