// **********************************************************************************
// 
// Name:    Date.cc
// Class:   <Date>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: A date label. Displays the date in the following format:
//              "Sun Oct 5, 12:48 PM".
//              
// Notes: Change to shorter update time once Atlas is more complete.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Date.h"
#include "../hdr/StatusSimple.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <cstdlib>
#include <string>
#include <ctime>

// Declares
StatusSimple* Date::widget;



// ////////////////////////////
// ///// GET CURRENT DATE /////
// ////////////////////////////

// Set the label for the date widget
std::string Date::now() {
    
    // Setup time struct
    std::string fmt = Config::fetch("date_fmt");
    time_t t        = time(0);
    struct tm* now  = localtime(&t);
    
    // Convert time struct to readable format
    char time_string[30];
    strftime(time_string, sizeof(time_string), fmt.c_str(), now);
    
    return std::string(time_string);
}



// ///////////////////////////////
// ///// DISPLAY DATE WIDGET /////
// ///////////////////////////////

// Display the date widget
void Date::create() {
    std::string font = Config::fetch("date_font");
    std::string size = Config::fetch("date_font_size");
    std::string text = now();
    
    widget = new StatusSimple();
    widget->init(text, font, atoi(size.c_str()));
    widget->update <Gtk::Label> (now, 1);
}
