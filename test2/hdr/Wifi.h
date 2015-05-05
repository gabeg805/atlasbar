// ============
// Header Guard
// ============

#ifndef WIFI_H
#define WIFI_H


// ========
// Includes
// ========

#include "../hdr/BarImage.h"
#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Wifi {
 public:
    static std::string    icon();
    void                  display(Gtk::Box *bar);
    
    static BarImage       *widget;
};

extern Wifi *wifi;

#endif
