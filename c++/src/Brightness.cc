// **********************************************************************************
// 
// Name:    Brightness.cc
// Class:   <Brightness>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: A brightness level indicator. Displays the brightness as a sun, and
//              as the brightness increases or decreases, the sun fills up or 
//              empties, respectively.
//              
// Notes: None.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Brightness.h"
#include "../hdr/StatusSimple.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <iostream>
#include <string>

// Declares    
StatusSimple<Gtk::Image> *Brightness::widget;



// /////////////////////////////////////
// ///// GET BRIGHTNESS ATTRIBUTES /////
// /////////////////////////////////////

// Return the proper brightness icon
std::string Brightness::icon() {
    
    // Icon path variables
    std::string name;
    std::string cmd = Config::fetch("brightness_cmd");
    std::string dir = Config::fetch("brightness_icon_dir");
    int level       = widget->percent(cmd);
    
    // Determine correct icon name
    if ( (level >= 0) && (level <= 15) )
        name = "0-15";
    else if ( (level > 15) && (level <= 30) )
        name = "15-30";
    else if ( (level > 30) && (level <= 45) )
        name = "30-45";
    else if ( (level > 45) && (level <= 60) )
        name = "45-60";
    else if ( (level > 60) && (level <= 75) )
        name = "60-75";
    else if ( (level > 75) && (level <= 100) )
        name = "75-100";
    else {
        std::cout << "Brightness: Could not match level" << level << std::endl;
        name = "75-100";
    }
    
    return (dir + name + ".png");
}



// /////////////////////////////////////
// ///// DISPLAY BRIGHTNESS WIDGET /////
// /////////////////////////////////////

// Display the brightness widget
void Brightness::create() {
    widget = new StatusSimple<Gtk::Image>( icon() );
    widget->padding(5, 0);
    widget->call(icon);
}
