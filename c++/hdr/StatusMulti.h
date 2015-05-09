// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef STATUSMULTI_H
#define STATUSMULTI_H


// ========
// Includes
// ========

#include "../hdr/StatusItem.h"
#include "../hdr/StatusBar.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

template <typename StatusType> 
class StatusMulti {
public:
    
    StatusMulti();
    StatusMulti(Gtk::Orientation opt);
    
    void                      populate(std::vector<std::string> arr);
    void                      populate(std::vector<std::string> arr, std::string font, int size);
    void                      call(int (*func)(int));
    bool                      set(int num);
    
    void                      attach(Gtk::Box *bar, StatusBar::Section sec);
    void                      background(std::string background);
    void                      foreground(std::string foreground);
    
    Gtk::Box                  *item;
    StatusItem<StatusType>    **multi;
    int                       (*updateCall)(int);
    int                       len;
    int                       index;
};


// Declares
template class StatusMulti<Gtk::Image>;
template class StatusMulti<Gtk::Label>;

#endif
