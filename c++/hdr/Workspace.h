// ============
// Header Guard
// ============

#ifndef WORKSPACE_H
#define WORKSPACE_H


// ========
// Includes
// ========

#ifndef DWM_COMPILE
#include "../hdr/StatusMulti.h"
#include <gtkmm.h>


// =======
// Classes
// =======

class Workspace {
 public:
    static int                        screen(int id);
    void                              display(Gtk::Box *bar);
    
    int                               tag;
    static StatusMulti<Gtk::Label>    *widget;
};


// Declares
extern Workspace *workspace;
#endif

// Declares
static const char *tags[] = { "1", "2", "3", "4", "5" };
// Dwm should call a function that Atlas compiles and outputs so that Dwm has 
// an updated version of the tags array
#define WORKSPACE_COMPILE

#endif
