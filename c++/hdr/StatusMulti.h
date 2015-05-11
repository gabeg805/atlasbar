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
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

template <typename atlas_w> 
class StatusMulti {
public:
    
    // Class variables
    Gtk::Box                 *item;
    StatusSimple<atlas_w>    **multi;
    std::vector<std::string> list;
    int                      (*updateCall)(int);
    int                      index;
    std::string              background;
    std::string              highlight;
    
    // Constructors
    StatusMulti(Gtk::Orientation opt) { 
        item       = Gtk::manage( new Gtk::Box(opt) ); 
        background = Config::fetch("background");
        highlight  = background;
    }
    
    StatusMulti(std::vector<std::string> arr, 
                Gtk::Orientation opt) 
    { 
        item       = Gtk::manage( new Gtk::Box(opt) ); 
        background = Config::fetch("background");
        highlight  = background;
        list       = arr;
    }
    
    StatusMulti(std::vector<std::string> arr, 
                std::string bg, 
                std::string hl, 
                Gtk::Orientation opt) 
    { 
        item       = Gtk::manage( new Gtk::Box(opt) ); 
        background = Config::fetch("background");
        highlight  = background;
        list       = arr;
    }
    
    StatusMulti(std::string bg, 
                std::string hl, 
                Gtk::Orientation opt) 
    { 
        item       = Gtk::manage( new Gtk::Box(opt) ); 
        background = bg;
        highlight  = hl;
    }
    
    // Member functions
    void                   populate();
    void                   populate(std::string font, int size);
    void                   populate(std::vector<std::string> arr);
    void                   populate(std::vector<std::string> arr, std::string font, int size);
    void                   call(int (*func)(int)) { updateCall = func; }
    bool                   set(int num);
    void                   color(std::string bg, std::string hl);
};



// ///////////////////////
// ///// APPLICATION /////
// ///////////////////////

// Fill up multi item statusbar application 
template <typename atlas_w>
inline void StatusMulti<atlas_w>::populate() {
    populate(list);
}



// Fill up multi item statusbar application 
template <>
inline void StatusMulti<Gtk::Label>::populate(std::string font, int size) {
    populate(list);
    
    // Setup each item in the multi item app
    for ( size_t i = 0; i < list.size(); ++i ) 
        StatusWidget::font(multi[i]->item, font, size);
}



// Fill up multi item statusbar application 
template <typename atlas_w>
inline void StatusMulti<atlas_w>::populate(std::vector<std::string> arr) {
    
    // Multi item statusbar app (try with std::vector)
    multi = new StatusSimple<atlas_w> *[arr.size()];
    
    // Setup each item in the multi item app
    std::vector<std::string>::iterator iter;
    index = 0;
    int i = 0;
    
    for ( iter = arr.begin(); iter != arr.end(); ++iter ) {
        multi[i] = new StatusSimple<atlas_w>(*iter);
        
        if ( i == index )
            StatusWidget::background(multi[i], highlight);
        else
            StatusWidget::background(multi[i], background);
        
        StatusWidget::attach(item, multi[i], StatusWidget::ALIGN_LEFT);
        StatusWidget::padding(multi[i], 5, 0);
        
        ++i;
    }
    
}



// Fill up multi item statusbar application 
template <>
inline void StatusMulti<Gtk::Label>::populate(std::vector<std::string> arr, 
                                              std::string font, 
                                              int size) 
{
    populate(arr);
    
    // Setup each item in the multi item app
    for ( size_t i = 0; i < arr.size(); ++i ) 
        StatusWidget::font(multi[i]->item, font, size);
}



// Interface to choose correct icon/label setter
template <typename atlas_w>
inline bool StatusMulti<atlas_w>::set(int num) {
    int loc = updateCall(num);
    
    StatusWidget::background(multi[loc],   highlight);
    StatusWidget::background(multi[index], background);
    
    index = loc;
    
    return true;
}



// Interface to choose correct icon/label setter
template <typename atlas_w>
inline void StatusMulti<atlas_w>::color(std::string bg, std::string hl) {
    background = bg;
    highlight  = hl;
}

#endif
