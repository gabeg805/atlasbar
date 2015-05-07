// ============
// Header Guard
// ============

#ifndef STATUSITEM_H
#define STATUSITEM_H


// ========
// Includes
// ========

#include "../hdr/StatusBar.hpp"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

template <typename StatusType> 
class StatusItem {
public:
    
    StatusItem();
    StatusItem(std::string str);
    
    int            percent(std::string cmd);
    void           call(std::string (*func)());
    void           update(std::string (*func)(), int time);
    bool           set();
    bool           set(StatusType *orig);
    
    void           attach(Gtk::Box *bar, StatusBar::Section sec);
    void           background(std::string background);
    void           foreground(std::string foreground);
    
    StatusType     *item;
    std::string    (*updateCall)();
};


// Declares
template class StatusItem<Gtk::Image>;
template class StatusItem<Gtk::Label>;

#endif
