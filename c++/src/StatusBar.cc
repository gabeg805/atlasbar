// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     StatusBar.cpp
// 
// 
// SYNTAX: 
// 
//     #include "StatusBar.hpp"
// 
// 
// PURPOSE:
// 
//     Write shit.
// 
// 
// MODIFICATION HISTORY:
// 
//     gabeg May 02 2015 <> Created.
// 
//     gabeg May 07 2015 <> Finished converting the C implementation to C++.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/StatusBar.hpp"

#include <gtkmm.h>
#include <gdkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>



// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

StatusBar::StatusBar() :
    Gtk::Window(Gtk::WINDOW_POPUP),
    bar(Gtk::ORIENTATION_HORIZONTAL, 5)
{
    set_title("Atlas");
    set_default_size(1366, 20);
    
    background = "#333333";
    foreground = "white";
    
    Gdk::RGBA back(background);
    Gdk::RGBA fore(foreground);
    
    override_background_color(back, Gtk::STATE_FLAG_NORMAL);
    override_color(fore, Gtk::STATE_FLAG_NORMAL);
    
    add(bar);
}
