// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef DATE_H
#define DATE_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Date {
 public:
    static std::string               now();
    void                             create();
    
    static StatusSimple<Gtk::Label>    *widget;
};


// Declares
extern Date *date;

#endif
