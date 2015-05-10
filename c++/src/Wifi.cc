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
//     #include "Wifi.h"
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
#include "../hdr/Wifi.h"
#include "../hdr/StatusSimple.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <iostream>
#include <string>

// Declares
StatusSimple<Gtk::Image> *Wifi::widget;



// ///////////////////////////////
// ///// GET WIFI ATTRIBUTES /////
// ///////////////////////////////

// Return the proper wifi icon
std::string Wifi::icon() {
    
    // Icon path variables
    std::string name;
    std::string cmd = Config::fetch("wifi_cmd");
    std::string dir = Config::fetch("wifi_icon_dir");
    int level       = widget->percent(cmd);
    
    // Determine correct icon name
    if ( level == 0 )
        name = "wireNone.png";
    else if ( (level > 0) && (level <= 20) )
        name = "wire0-20.png";
    else if ( (level > 20) && (level <= 40) )
        name = "wire20-40.png";
    else if ( (level > 40) && (level <= 60) )
        name = "wire40-60.png";
    else if ( (level > 60) && (level <= 80) )
        name = "wire60-80.png";
    else if ( (level > 80) && (level <= 100) )
        name = "wire80-100.png";
    else {
        std::cout << "Wifi: Could not match level " << level << std::endl;
        name = "wireNone.png";
    }
    
    return (dir + name);
}



// ///////////////////////////////
// ///// DISPLAY WIFI WIDGET /////
// ///////////////////////////////

// Display the wifi widget
void Wifi::create() {
    widget = new StatusSimple<Gtk::Image>( icon() );
    widget->padding(5, 0);
    widget->update(icon, 5);
}
