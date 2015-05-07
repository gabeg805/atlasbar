// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     Wifi.cc
// 
// 
// SYNTAX: 
// 
//     #include "Wifi.hpp"
// 
// 
// PURPOSE:
// 
//     Creates a wifi icon and attaches it to the status bar. Displays wifi
//     level as a series of bars showing the reception level.
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
#include "../hdr/Wifi.hpp"
#include "../hdr/StatusItem.hpp"
#include "../hdr/StatusBar.hpp"

#include <gtkmm.h>
#include <iostream>
#include <string>

// Declares
StatusItem<Gtk::Image> *Wifi::widget;



// ///////////////////////////////
// ///// GET WIFI ATTRIBUTES /////
// ///////////////////////////////

// Return the proper wifi icon
std::string Wifi::icon() {
    
    // Initialize variables
    std::string name;
    std::string icon_dir = "/home/gabeg/.config/awesome/img/icons/wifi/";
    std::string icon_ext = ".png";
    std::string cmd      = "/home/gabeg/.config/dwm/src/atlas/scripts/wifi";
    int level            = widget->percent(cmd);
    std::cout << "Wifi: " << level << std::endl;
    
    // Determine the correct wifi icon
    if ( level == 0 )
        name = "wireNone";
    else if ( (level > 0) && (level <= 20) )
        name = "wire0-20";
    else if ( (level > 20) && (level <= 40) )
        name = "wire20-40";
    else if ( (level > 40) && (level <= 60) )
        name = "wire40-60";
    else if ( (level > 60) && (level <= 80) )
        name = "wire60-80";
    else if ( (level > 80) && (level <= 100) )
        name = "wire80-100";
    else {
        std::cout << "Wifi: Could not match level " << level << std::endl;
        name = "wireNone";
    }
    
    // Allocate memory for string
    std::string path = icon_dir + name + icon_ext;
    std::cout << "Wifi: " << path << std::endl;
    
    return path;
}



// ///////////////////////////////
// ///// DISPLAY WIFI WIDGET /////
// ///////////////////////////////

// Display the wifi widget
void Wifi::display(Gtk::Box *bar) {
    std::string path = icon();
    
    widget = new StatusItem<Gtk::Image>(path);
    widget->attach(bar, StatusBar::ALIGN_RIGHT);
    widget->update(icon, 5);
}
