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
//     #include "Brightness.h"
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
        name = "bright0-15.png";
    else if ( (level > 15) && (level <= 30) )
        name = "bright15-30.png";
    else if ( (level > 30) && (level <= 45) )
        name = "bright30-45.png";
    else if ( (level > 45) && (level <= 60) )
        name = "bright45-60.png";
    else if ( (level > 60) && (level <= 75) )
        name = "bright60-75.png";
    else if ( (level > 75) && (level <= 100) )
        name = "bright75-100.png";
    else {
        std::cout << "Brightness: Could not match level" << level << std::endl;
        name = "bright75-100.png";
    }
    
    return (dir + name);
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
