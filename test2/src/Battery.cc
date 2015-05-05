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
//     #include "/PATH/TO/HEADER/Battery.h"
// 
// 
// PURPOSE:
// 
//     Creates a battery icon widget on the main status bar. Displays battery
//     level as a circular icon that changes color (from green to yellow to red)
//     as the battery level decreases.
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg Sep 15 2014 <> created
// 
//     gabeg Oct 05 2014 <> Added a header to the source file.
// 
//     gabeg Nov 02 2014 <> Made it so that the battery widget did not have to rely 
//                          on the Atlas frame (being passed in as a parameter). 
// 
//     gabeg May 02 2014 <> Removed excessive parts of the header.
//                          Made every widget attach to one Application, instead of 
//                          being separate entities.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/BarImage.h"
#include "../hdr/StatusBar.h"
#include "../hdr/Battery.h"
#include "../hdr/util.h"

#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

BarImage *Battery::widget;



// //////////////////////////////////
// ///// GET BATTERY ATTRIBUTES /////
// //////////////////////////////////

// Return the proper battery icon
string Battery::icon() {
    
    // Initialize variables
    string icon_dir = "/home/gabeg/.config/awesome/img/icons/bat/bat";
    string icon_suf = "-charge";
    string icon_ext = ".png";
    string cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/bat";
    int charge      = get_percent(cmd);
    
    // Determine the correct volume icon
    stringstream ss;
    ss << charge;
    string path = icon_dir + ss.str() + icon_ext;
    
    return path;
}



// //////////////////////////////////
// ///// DISPLAY BATTERY WIDGET /////
// //////////////////////////////////

// Display the battery widget
void Battery::display(Gtk::Box *bar) {
    string path = icon();
    widget = new BarImage(bar, path);
    widget->position(StatusBar::RIGHT);
    widget->update(icon, 10);
}
