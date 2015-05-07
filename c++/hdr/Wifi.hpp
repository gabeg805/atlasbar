// ============
// Header Guard
// ============

#ifndef WIFI_H
#define WIFI_H


// ========
// Includes
// ========

#include "../hdr/StatusItem.hpp"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Wifi {
 public:
    static std::string               icon();
    void                             display(Gtk::Box *bar);
    
    static StatusItem<Gtk::Image>    *widget;
};


// Declares
extern Wifi *wifi;

#endif
