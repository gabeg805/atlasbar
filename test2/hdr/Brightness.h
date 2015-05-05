// ============
// Header Guard
// ============

#ifndef BRIGHT_H
#define BRIGHT_H


// ========
// Includes
// ========

#include "../hdr/BarImage.h"
#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Brightness {
 public:
    void                  set();
    static std::string    icon();
    void                  display(Gtk::Box *bar);
    
    static BarImage       *widget;
};

extern Brightness *brightness;

#endif
