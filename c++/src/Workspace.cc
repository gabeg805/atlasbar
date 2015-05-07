// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     tags.cpp
// 
// 
// SYNTAX: 
// 
//     #include "Workspace.hpp"
// 
// 
// PURPOSE:
// 
//     Creates workspace indicator labels and attaches the labels to the status bar.
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
#include "../hdr/Workspace.hpp"
#include "../hdr/StatusMulti.hpp"
#include "../hdr/StatusItem.hpp"
#include "../hdr/StatusBar.hpp"

#include <gtkmm.h>
#include <iostream>
#include <string>

// Declares
StatusMulti<Gtk::Label> *Workspace::widget;



// ////////////////////////////
// ///// SCREEN TAG INDEX /////
// ////////////////////////////

// Return the index of the screen tag
int Workspace::screen(int id) {
    int i = 0;
    
    while ( id != 0 ) {
        id >>= 1;
        ++i;
    }
    
    return (i-1);
}



// ///////////////////////////////
// ///// DISPLAY TAGS WIDGET /////
// ///////////////////////////////

// Display the tags widget
void Workspace::display(Gtk::Box *bar) {
    std::string names[] = {"1", "2", "3", "4", "5"};
    int len        = sizeof(names) / sizeof(names[0]);
    
    widget = new StatusMulti<Gtk::Label>(Gtk::ORIENTATION_HORIZONTAL);
    widget->populate(names, len);
    widget->call(screen);
    widget->attach(bar, StatusBar::ALIGN_LEFT);
}
