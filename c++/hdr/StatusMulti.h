// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef STATUSMULTI_H
#define STATUSMULTI_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"
#include "../hdr/Statusbar.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

template <typename atlas_w> 
class StatusMulti {
public:
    StatusMulti(Gtk::Orientation opt);
    
    void                   populate(std::vector<std::string> arr);
    void                   populate(std::vector<std::string> arr, std::string font, int size);
    void                   call(int (*func)(int));
    bool                   set(int num);
    
    Gtk::Box               *item;
    StatusSimple<atlas_w>  **child;
    int                    (*updateCall)(int);
    int                    index;
};


// Declares
template class StatusMulti<Gtk::Image>;
template class StatusMulti<Gtk::Label>;

#endif
