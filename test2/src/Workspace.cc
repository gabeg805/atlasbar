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
//     #include "/PATH/TO/HEADER/tags.h"
// 
// 
// PURPOSE:
// 
//     Creates a tags widget on the main status bar that displays the tags in 
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
//     gabeg Nov 02 2014 <> Made it so that the tags widget did not have to rely on 
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
#include "../hdr/StatusBar.h"
#include "../hdr/BarLabel.h"
#include "../hdr/Workspace.h"
#include "../hdr/util.h"

#include <gtkmm.h>
#include <iostream>
#include <string>

using namespace std;

Gtk::Box *Workspace::widget;



Workspace::Workspace() {
    names[0] = "1";
    names[1] = "2";
    names[2] = "3";
    names[3] = "4";
    names[4] = "5";
    
    tag      = 1;
    len      = sizeof(names) / sizeof(names[0]);
}



// ////////////////////////////
// ///// SCREEN TAG INDEX /////
// ////////////////////////////

// Return the index of the screen tag
int Workspace::index(int id) {
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

void Workspace::set(int id) {
    tag = index(id);
}


// Display the tags widget
void Workspace::display(Gtk::Box *bar) {
    widget         = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL);
    
    int i;
    for ( i=0; i < len; ++i ) {
        // cout << "Tag: " << names[i] << endl;
        
        BarLabel label(widget, names[i]);
        
        if ( i == index(tag) )
            label.background("#999999");
        else
            label.background("#333333");
        
        label.position(StatusBar::LEFT);
        label.padding(5, 0);
    }
    
    bar->pack_start(*widget, Gtk::PACK_SHRINK);
}
