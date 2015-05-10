// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     Battery.cc
// 
// 
// SYNTAX: 
// 
//     #include "Battery.h"
// 
// 
// PURPOSE:
// 
//     Creates a battery icon and attaches it to the status bar. Displays battery
//     level as a circular icon that changes color (from green to yellow to red)
//     as the battery level decreases.
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
    
    return (dir + "bat" + ss.str() + ".png");
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
