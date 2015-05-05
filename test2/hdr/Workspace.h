// ============
// Header Guard
// ============

#ifndef WORKSPACE_H
#define WORKSPACE_H


// ========
// Includes
// ========

#include "../hdr/StatusBar.h"
#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Workspace {
 public:
    Workspace();
    int                index(int id);
    void               set(int id);
    void               display(Gtk::Box *bar);
    
    int                tag;
    int                len;
    std::string        names[5];
    static Gtk::Box    *widget;
};

extern Workspace *workspace;

#endif
