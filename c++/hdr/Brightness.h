// ============
// Header Guard
// ============

#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H


// ========
// Includes
// ========

#include "../hdr/StatusItem.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Brightness {
public:
    static std::string               icon();
    void                             display(Gtk::Box *bar);
    
    static StatusItem<Gtk::Image>    *widget;
};


// Declares
extern Brightness *brightness;

#endif
