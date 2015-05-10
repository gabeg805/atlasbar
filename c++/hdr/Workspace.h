// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef WORKSPACE_H
#define WORKSPACE_H


// ========
// Includes
// ========

#include "../hdr/StatusMulti.h"

#include <gtkmm.h>


// =======
// Classes
// =======

class Workspace {
 public:
    static int                        screen(int id);
    void                              create();
    
    static StatusMulti<Gtk::Label>    *widget;
};


// Declares
extern Workspace *workspace;

#endif
