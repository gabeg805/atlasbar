// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     BarImage.cc
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/BarImage.h"
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
#include "../hdr/BarImage.h"
#include "../hdr/StatusBar.h"

#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

// Gtk::Image *BarImage::icon;


// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

BarImage::BarImage() {
}

BarImage::BarImage(Gtk::Box *bar, string path) {
    item = Gtk::manage( new Gtk::Image(path) );
    box   = bar;
}

void BarImage::set(string (*func)()) {
    item->set( func() );
}

void BarImage::position(StatusBar::Section sec) {
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

void BarImage::padding(int x, int y) {
    item->set_padding(x, y);
}

void BarImage::background(string background) {
    Gdk::RGBA color(background);
    item->override_background_color(color, Gtk::STATE_FLAG_NORMAL);
}

void BarImage::foreground(string foreground) {
    Gdk::RGBA color(foreground);
    item->override_color(color, Gtk::STATE_FLAG_NORMAL);
}

void BarImage::update(string (*func)(), int time) {
    sigc::slot<bool, Gtk::Image*, string(*)()> pack = 
        sigc::mem_fun(*this, &BarImage::timeout);
    Glib::signal_timeout().connect_seconds(sigc::bind<Gtk::Image*, string(*)()>(pack, item, func), time);
}

bool BarImage::timeout(Gtk::Image *orig, string (*func)()) {
    orig->set( func() );
    return true;
}
