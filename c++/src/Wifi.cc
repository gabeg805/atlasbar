// **********************************************************************************
// 
// Name:    Wifi.cc
// Class:   <Wifi>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: A wifi strength indicator. Displays wifi strength as a series of bars
//              (like a phone's signal strength icon) showing the reception level.
//              
// Notes: None.
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
StatusSimple* Wifi::widget;



// ///////////////////////////////
// ///// GET WIFI ATTRIBUTES /////
// ///////////////////////////////

// Return the proper wifi icon
std::string Wifi::icon() {
    std::string name;
    std::string cmd = Config::fetch("wifi_cmd");
    std::string dir = Config::fetch("wifi_icon_dir");
    int level       = StatusWidget::percent(cmd);
    
    // Determine correct icon name
    if ( level == 0 )
        name = "None";
    else if ( (level > 0) && (level <= 20) )
        name = "0-20";
    else if ( (level > 20) && (level <= 40) )
        name = "20-40";
    else if ( (level > 40) && (level <= 60) )
        name = "40-60";
    else if ( (level > 60) && (level <= 80) )
        name = "60-80";
    else if ( (level > 80) && (level <= 100) )
        name = "80-100";
    else {
        std::cout << "Wifi: Could not match level " << level << std::endl;
        name = "None";
    }
    
    return (dir + name + ".png");
}



// ///////////////////////////////
// ///// DISPLAY WIFI WIDGET /////
// ///////////////////////////////

// Display the wifi widget
void Wifi::create() {
    widget = new StatusSimple();
    widget->init    <Gtk::Image> (icon());
    widget->padding <Gtk::Image> (5, 0);
    widget->update  <Gtk::Image> (icon, 5);
}
