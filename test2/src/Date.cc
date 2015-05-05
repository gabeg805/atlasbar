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
//     #include "/PATH/TO/HEADER/Date.h"
// 
// 
// PURPOSE:
// 
//     Creates a date widget on the main status bar that displays the date in 
//     the format: "Sun Oct 5, 12:48 PM".
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
//     gabeg Nov 02 2014 <> Made it so that the date widget did not have to rely on 
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
#include "../hdr/Date.h"
#include "../hdr/BarLabel.h"
#include "../hdr/StatusBar.h"

#include <gtkmm.h>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

BarLabel *Date::widget;



// ////////////////////////////
// ///// GET CURRENT DATE /////
// ////////////////////////////

// Set the label for the date widget
string Date::now() {
    
    // Setup time struct
    string fmt = "%a %b %-d, %-I:%M:%S %p";
    time_t t        = time(0);
    struct tm * now = localtime(&t);
    
    // Convert time struct to readable format
    char time_string[30];
    strftime(time_string, sizeof(time_string), fmt.c_str(), now);
    
    return string(time_string);
}



// ///////////////////////////////
// ///// DISPLAY DATE WIDGET /////
// ///////////////////////////////

// Display the date widget
void Date::display(Gtk::Box *bar) {
    string text = now();
    widget = new BarLabel(bar, text);
    widget->position(StatusBar::CENTER);
    widget->update(now, 1);
}
