// ============
// Header Guard
// ============

#ifndef DATE_H
#define DATE_H


// ========
// Includes
// ========

#include "../hdr/StatusItem.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Date {
 public:
    static std::string               now();
    void                             display(Gtk::Box *bar);
    
    static StatusItem<Gtk::Label>    *widget;
};


// Declares
extern Date *date;

#endif
