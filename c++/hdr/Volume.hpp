// ============
// Header Guard
// ============

#ifndef VOLUME_H
#define VOLUME_H


// ========
// Includes
// ========

#include "../hdr/StatusItem.hpp"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Volume {
 public:
    static std::string               icon();
    void                             display(Gtk::Box *bar);
    
    static StatusItem<Gtk::Image>    *widget;
};


// Declares
extern Volume *volume;

#endif
