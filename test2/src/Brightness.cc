// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     Brightness.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/Brightness.h"
// 
// 
// PURPOSE:
// 
//     Creates a brightness icon widget on the main status bar. Displays 
//     brightness level as a sun that fills up as the brightness increases.
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
//     gabeg Nov 02 2014 <> Made it so that the brightness widget did not have to 
//                          rely on the Atlas frame (being passed in as a parameter). 
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
#include "../hdr/Brightness.h"
#include "../hdr/util.h"

#include <gtkmm.h>
#include <iostream>
#include <string>

using namespace std;

BarImage *Brightness::widget;



// /////////////////////////////////////
// ///// GET BRIGHTNESS ATTRIBUTES /////
// /////////////////////////////////////

void Brightness::set() {
    widget->set(icon);
}

// Return the proper brightness icon
string Brightness::icon() {
    
    // Initialize variables
    string icon_dir = "/home/gabeg/.config/awesome/img/icons/bright/";
    string icon_ext = ".png";
    string cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/bright";
    int level       = get_percent(cmd);
    string name;
    
    // Determine the correct brightness icon
    if ( (level >= 0) && (level <= 15) )
        name = "bright0-15";
    else if ( (level > 15) && (level <= 30) )
        name = "bright15-30";
    else if ( (level > 30) && (level <= 45) )
        name = "bright30-45";
    else if ( (level > 45) && (level <= 60) )
        name = "bright45-60";
    else if ( (level > 60) && (level <= 75) )
        name = "bright60-75";
    else if ( (level > 75) && (level <= 100) )
        name = "bright75-100";
    else {
        cout << "ERROR: Could not match level" << level << endl;
        name = "bright75-100";
    }
    
    // Allocate memory for string
    string path = icon_dir + name + icon_ext;
    
    return path;
}



// /////////////////////////////////////
// ///// DISPLAY BRIGHTNESS WIDGET /////
// /////////////////////////////////////

// Display the brightness widget
void Brightness::display(Gtk::Box *bar) {
    string path = icon();
    widget = new BarImage(bar, path);
    widget->position(StatusBar::RIGHT);
}
