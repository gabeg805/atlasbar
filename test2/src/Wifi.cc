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
//     #include "/PATH/TO/HEADER/Wifi.h"
// 
// 
// PURPOSE:
// 
//     Creates a wifi icon widget on the main status bar. Displays wifi
//     level as a series of bars showing the reception level.
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
//     gabeg Nov 02 2014 <> Made it so that the wifi widget did not have to rely on 
//                          the Atlas frame (being passed in as a parameter). 
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
#include "../hdr/Wifi.h"
#include "../hdr/util.h"

#include <gtkmm.h>
#include <iostream>
#include <string>

using namespace std;

BarImage *Wifi::widget;



// ///////////////////////////////
// ///// GET WIFI ATTRIBUTES /////
// ///////////////////////////////

// Return the proper wifi icon
string Wifi::icon() {
    
    // Initialize variables
    string icon_dir = "/home/gabeg/.config/awesome/img/icons/wifi/";
    string icon_ext = ".png";
    string cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/wifi";
    int level       = get_percent(cmd);
    string name;
    
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
        cout << "ERROR: Could not match level " << level << endl;
        name = "wireNone";
    }
    
    // Allocate memory for string
    string path = icon_dir + name + icon_ext;
    return path;
}



// ///////////////////////////////
// ///// DISPLAY WIFI WIDGET /////
// ///////////////////////////////

// Display the wifi widget
void Wifi::display(Gtk::Box *bar) {
    string path = icon();
    widget = new BarImage(bar, path);
    widget->position(StatusBar::RIGHT);
    widget->update(icon, 5);
}
