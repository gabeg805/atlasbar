// **********************************************************************************
// 
// Name:    Battery.cc
// Class:   <Battery>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: A battery charge indicator. Displays the battery in a circular icon
//              and as the charge decreases, the icon changes color from green to 
//              yellow, and then red.
//              
// Notes: None.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Battery.h"
#include "../hdr/StatusSimple.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <sstream>
#include <string>

// Declares
StatusSimple<Gtk::Image> *Battery::widget;



// //////////////////////////////////
// ///// GET BATTERY ATTRIBUTES /////
// //////////////////////////////////

// Return the proper battery icon
std::string Battery::icon() {
    
    // Icon path variables
    std::stringstream ss;
    std::string dir = Config::fetch("battery_icon_dir");
    std::string cmd = Config::fetch("battery_cmd");
    int level       = widget->percent(cmd);
    ss << level;
    
    return (dir + ss.str() + ".png");
}



// //////////////////////////////////
// ///// DISPLAY BATTERY WIDGET /////
// //////////////////////////////////

// Display the battery widget
void Battery::create() {
    widget = new StatusSimple<Gtk::Image>( icon() );
    widget->padding(5, 0);
    widget->update(icon, 30);
}
