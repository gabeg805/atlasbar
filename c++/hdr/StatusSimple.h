// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef STATUSITEM_H
#define STATUSITEM_H


// ========
// Includes
// ========

#include "../hdr/StatusWidget.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

template <typename atlas_w>
class StatusSimple : public StatusWidget {
public:
    StatusSimple(std::string str);
    StatusSimple(std::string str, std::string font, int size);
    
    void           call(std::string (*func)());
    void           update(std::string (*func)(), int time);
    bool           set();
    bool           set(atlas_w *orig);
    int            percent(std::string cmd);
    void           padding(int x, int y) { StatusWidget::padding(item, x, y); }
    
    atlas_w        *item;
    std::string    (*updateCall)();
};


// Declares
template class StatusSimple<Gtk::Image>;
template class StatusSimple<Gtk::Label>;

#endif
