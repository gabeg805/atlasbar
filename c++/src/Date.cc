// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     Date.cc
// 
// 
// SYNTAX: 
// 
//     #include "Date.h"
// 
// 
// PURPOSE:
// 
//     Creates a date label on the status bar that displays the current date in the 
//     following format: "Sun Oct 5, 12:48 PM".
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
#include "../hdr/Date.h"
#include "../hdr/StatusSimple.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <cstdlib>
#include <string>
#include <ctime>

// Declares
StatusSimple<Gtk::Label> *Date::widget;



// ////////////////////////////
// ///// GET CURRENT DATE /////
// ////////////////////////////

// Set the label for the date widget
std::string Date::now() {
    
    // Setup time struct
    std::string fmt = Config::fetch("date_fmt");
    time_t t        = time(0);
    struct tm * now = localtime(&t);
    
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
    
    widget = new StatusSimple<Gtk::Label>( text, font, atoi(size.c_str()) );
    widget->update(now, 1);
}
