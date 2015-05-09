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
#include "../hdr/StatusItem.h"
#include "../hdr/StatusBar.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <string>
#include <ctime>

// Declares
StatusItem<Gtk::Label> *Date::widget;



// ////////////////////////////
// ///// GET CURRENT DATE /////
// ////////////////////////////

// Set the label for the date widget
std::string Date::now() {
    
    // Setup time struct
    std::string file = "/home/gabeg/.config/dwm/src/atlas/c++/config/Atlas.config";
    std::string fmt = Config::read(file, "date_fmt");
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
void Date::display(Gtk::Box *bar) {
    std::string text = now();
    
    widget = new StatusItem<Gtk::Label>(text, "GohuFont", 9);
    widget->attach(bar, StatusBar::ALIGN_CENTER);
    widget->update(now, 1);
}
