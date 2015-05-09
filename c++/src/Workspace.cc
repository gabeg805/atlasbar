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
//     #include "Workspace.h"
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
#include "../hdr/Workspace.h"
#include "../hdr/StatusMulti.h"
#include "../hdr/StatusItem.h"
#include "../hdr/StatusBar.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <iostream>
#include <string>
#include <vector>

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
    
    std::string file = "/home/gabeg/.config/dwm/src/atlas/c++/config/Atlas.config";
    std::string line = Config::read(file, "workspace_tags");
    std::vector<std::string> taggeries = Config::parse(line, ',');
    
    widget = new StatusMulti<Gtk::Label>(Gtk::ORIENTATION_HORIZONTAL);
    widget->populate(taggeries, "GohuFont", 9);
    widget->call(screen);
    widget->attach(bar, StatusBar::ALIGN_LEFT);
}
