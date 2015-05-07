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
//     #include "Brightness.hpp"
// 
// 
// PURPOSE:
// 
//     Creates a brightness icon and attaches it to the status bar. Displays 
//     brightness level as a sun that fills up as the brightness increases.
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
#include "../hdr/Brightness.hpp"
#include "../hdr/StatusItem.hpp"
#include "../hdr/StatusBar.hpp"

#include <gtkmm.h>
#include <iostream>
#include <string>

// Declares    
StatusItem<Gtk::Image> *Brightness::widget;



// /////////////////////////////////////
// ///// GET BRIGHTNESS ATTRIBUTES /////
// /////////////////////////////////////

// Return the proper brightness icon
std::string Brightness::icon() {
    
    // Initialize variables
    std::string name;
    std::string icon_dir = "/home/gabeg/.config/awesome/img/icons/bright/";
    std::string icon_ext = ".png";
    std::string cmd      = "/home/gabeg/.config/dwm/src/atlas/scripts/bright";
    int level            = widget->percent(cmd);
    std::cout << "Brightness: " << level << std::endl;
    
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
        std::cout << "Brightness: Could not match level" << level << std::endl;
        name = "bright75-100";
    }
    
    // Allocate memory for string
    std::string path = icon_dir + name + icon_ext;
    std::cout << "Brightness: " << path << std::endl;
    
    return path;
}



// /////////////////////////////////////
// ///// DISPLAY BRIGHTNESS WIDGET /////
// /////////////////////////////////////

// Display the brightness widget
void Brightness::display(Gtk::Box *bar) {
    std::string path = icon();
    
    widget = new StatusItem<Gtk::Image>(path);
    widget->attach(bar, StatusBar::ALIGN_RIGHT);
    widget->call(icon);
}
