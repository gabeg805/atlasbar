// **********************************************************************************
// 
// Name:    Statusbar.cc
// Class:   <Statusbar>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The Atlas Statusbar container. It contains all applications that will
//              go on the statusbar.
//              
// Notes: None.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Statusbar.h"
#include "../hdr/StatusSignal.h"
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
    Gtk::Window(Gtk::WINDOW_POPUP),
    bar(Gtk::ORIENTATION_HORIZONTAL)
{
    // Determine bar orientation
    std::string width       = Config::fetch("width");
    std::string height      = Config::fetch("height");
    std::string background  = Config::fetch("background");
    std::string foreground  = Config::fetch("foreground");
    std::string orientation = Config::fetch("orientation");
    Gdk::RGBA back(background);
    Gdk::RGBA fore(foreground);
    
    set_title("Atlas");
    set_default_size( atoi(width.c_str()), atoi(height.c_str()) );
    override_background_color(back, Gtk::STATE_FLAG_NORMAL);
    override_color(fore, Gtk::STATE_FLAG_NORMAL);
    
    if ( orientation.compare("vertical") == 0 )
        bar.set_orientation(Gtk::ORIENTATION_VERTICAL);
    else
        bar.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    
    add(bar);
    
    signal(SIGUSR1, StatusSignal::statusSigCatcher);
}
