// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     BarLabel.cc
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/BarLabel.h"
// 
// 
// PURPOSE:
// 
//     Write shit.
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg May 02 2014 <> Removed excessive parts of the header.
//                          Made every widget attach to one Application, instead of 
//                          being separate entities.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/BarLabel.h"
#include "../hdr/StatusBar.h"

#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;


// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

BarLabel::BarLabel(Gtk::Box *bar, string text) {
    item = Gtk::manage( new Gtk::Label(text) );
    box   = bar;
}

void BarLabel::set(string (*func)()) {
    item->set_text( func() );
}

void BarLabel::position(StatusBar::Section sec) {
    switch ( sec ) {
    case StatusBar::LEFT:
        box->pack_start(*item, Gtk::PACK_SHRINK);
        break;
    case StatusBar::CENTER:
        box->set_center_widget(*item);
        break;
    case StatusBar::RIGHT:
        box->pack_end(*item, Gtk::PACK_SHRINK);
        break;
    }
}

void BarLabel::padding(int x, int y) {
    item->set_padding(x, y);
}

void BarLabel::background(string background) {
    Gdk::RGBA color(background);
    item->override_background_color(color, Gtk::STATE_FLAG_NORMAL);
}

void BarLabel::foreground(string foreground) {
    Gdk::RGBA color(foreground);
    item->override_color(color, Gtk::STATE_FLAG_NORMAL);
}

void BarLabel::update(string (*func)(), int time) {
    sigc::slot<bool, Gtk::Label*, string(*)()> pack = 
        sigc::mem_fun(*this, &BarLabel::timeout);
    Glib::signal_timeout().connect_seconds(sigc::bind<Gtk::Label*, string(*)()>(pack, item, func), time);

    // sigc::slot<bool, string(*)()> pack = 
    //     sigc::mem_fun(*this, &BarLabel::timeout);
    // Glib::signal_timeout().connect_seconds(sigc::bind<string(*)()>(pack, func), time);
}

bool BarLabel::timeout(Gtk::Label *orig, string (*func)()) {
    orig->set_text( func() );
    return true;
}
