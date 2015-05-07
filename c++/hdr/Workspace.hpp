// ============
// Header Guard
// ============

#ifndef WORKSPACE_H
#define WORKSPACE_H


// ========
// Includes
// ========

#include "../hdr/StatusMulti.hpp"

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
