// ============
// Header Guard
// ============

#ifndef BAT_H
#define BAT_H


// ========
// Includes
// ========

#include "../hdr/BarImage.h"
#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Battery {
 public:
    static std::string    icon();
    void                  display(Gtk::Box *bar);
    
    static BarImage       *widget;
};

extern Battery *battery;

#endif
