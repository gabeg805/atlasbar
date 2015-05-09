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
#include "../hdr/StatusItem.h"
#include "../hdr/StatusBar.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <string>

// Declares
StatusItem<Gtk::Image> *Battery::widget;



// //////////////////////////////////
// ///// GET BATTERY ATTRIBUTES /////
// //////////////////////////////////

// Return the proper battery icon
std::string Battery::icon() {
    
    // Initialize variables
    std::string file = "/home/gabeg/.config/dwm/src/atlas/c++/config/Atlas.config";
    std::string cmd = Config::read(file, "battery_cmd");
    
    std::string icon_dir = "/home/gabeg/.config/awesome/img/icons/bat/bat";
    std::string icon_suf = "-charge";
    std::string icon_ext = ".png";
    int level            = widget->percent(cmd);
    std::cout << "Battery: " << level << std::endl;
    
    // Determine the correct volume icon
    std::stringstream ss;
    ss << level;
    
    std::string path = icon_dir + ss.str() + icon_ext;
    std::cout << "Battery: " << path << std::endl;
    
    return path;
}



// //////////////////////////////////
// ///// DISPLAY BATTERY WIDGET /////
// //////////////////////////////////

// Display the battery widget
void Battery::display(Gtk::Box *bar) {
    std::string path = icon();
    
    widget = new StatusItem<Gtk::Image>(path);
    widget->attach(bar, StatusBar::ALIGN_RIGHT);
    widget->update(icon, 30);
}
