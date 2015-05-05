// ============
// Header Guard
// ============

#ifndef VOL_H
#define VOL_H

// ========
// Includes
// ========

#include "../hdr/BarImage.h"
#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Volume {
 public:
    void                  set();
    static std::string    icon();
    void                  display(Gtk::Box *bar);
    
    static BarImage       *widget;
};

extern Volume *volume;

#endif
