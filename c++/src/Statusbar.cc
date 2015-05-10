// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     Statusbar.cpp
// 
// 
// SYNTAX: 
// 
//     #include "Statusbar.h"
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
#include "../hdr/Statusbar.h"
#include "../hdr/StatusWatcher.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <gdkmm.h>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include <string>



// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

Statusbar::Statusbar() :
    Gtk::Window(Gtk::WINDOW_POPUP)
{
    bar = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
    
    std::string width      = Config::fetch("width");
    std::string height     = Config::fetch("height");
    std::string background = Config::fetch("background");
    std::string foreground = Config::fetch("foreground");
    Gdk::RGBA back(background);
    Gdk::RGBA fore(foreground);
    
    set_title("Atlas");
    set_default_size( atoi(width.c_str()), atoi(height.c_str()) );
    
    override_background_color(back, Gtk::STATE_FLAG_NORMAL);
    override_color(fore, Gtk::STATE_FLAG_NORMAL);
    
    add(*bar);
    
    signal(SIGUSR1, statusWatcher);
}
