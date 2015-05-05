// ============
// Header Guard
// ============

#ifndef DATE_H
#define DATE_H


// ========
// Includes
// ========

#include "../hdr/BarLabel.h"
#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Date {
 public:
    static std::string    now();
    void                  display(Gtk::Box *bar);
    
    static BarLabel       *widget;
};

extern Date *date;

#endif
