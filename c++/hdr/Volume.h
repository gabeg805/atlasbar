// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef VOLUME_H
#define VOLUME_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Volume {
 public:
    static std::string               icon();
    void                             create();
    
    static StatusSimple<Gtk::Image>    *widget;
};


// Declares
extern Volume *volume;

#endif
