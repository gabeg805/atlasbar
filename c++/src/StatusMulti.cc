// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     StatusMulti.cc
// 
// 
// SYNTAX: 
// 
//     #include "StatusMulti.hpp"
// 
// 
// PURPOSE:
// 
//     A container to initialize and hold multiple statusbar items of one type
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
#include "../hdr/StatusMulti.hpp"
#include "../hdr/StatusItem.hpp"
#include "../hdr/StatusBar.hpp"

#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>



// ////////////////////////
// ///// CONSTRUCTORS /////
// ////////////////////////

// Default empty constructor
template <typename StatusType>
StatusMulti<StatusType>::StatusMulti() {
}



// Construct a container for multiple status bar items
template <typename StatusType>
StatusMulti<StatusType>::StatusMulti(Gtk::Orientation opt) {
    item = Gtk::manage( new Gtk::Box(opt) ); 
}



// ///////////////////////
// ///// APPLICATION /////
// ///////////////////////

// Fill up multi item statusbar application 
template <typename StatusType>
void StatusMulti<StatusType>::populate(std::string arr[], int n) {
    
    // Multi item statusbar app
    multi = new StatusItem<StatusType> *[n];
    
    // Setup each item in the multi item app
    index = 0;
    len = n; 
    int i;
    
    for ( i=0; i < len; ++i ) {
        multi[i] = new StatusItem<StatusType>(arr[i]);
        
        if ( i == index )
            multi[i]->background("#999999");
        else
            multi[i]->background("#333333");
        
        multi[i]->attach(item, StatusBar::ALIGN_LEFT);
        multi[i]->item->set_padding(5, 0);
    }
    
}



// Set a function to call when updating statusbar icon/label
template <typename StatusType>
void StatusMulti<StatusType>::call(int (*func)(int)) {
    updateCall = func;
}



// Interface to choose correct icon/label setter
template <typename StatusType>
bool StatusMulti<StatusType>::set(int num) {
    int loc = updateCall(num);
    
    multi[loc]->background("#999999");
    multi[index]->background("#333333");
    
    index = loc;
    
    return true;
}



// ///////////////////
// ///// STYLING /////
// ///////////////////

// StatusItem also uses this, try and make it so that it's not in both files
// Set the region of the statusbar to display the item (left/center/right);
template <typename StatusType>
void StatusMulti<StatusType>::attach(Gtk::Box *bar, StatusBar::Section sec) {
    switch ( sec ) {
    case StatusBar::ALIGN_LEFT:
        bar->pack_start(*item, Gtk::PACK_SHRINK);
        break;
    case StatusBar::ALIGN_CENTER:
        bar->set_center_widget(*item);
        break;
    case StatusBar::ALIGN_RIGHT:
        bar->pack_end(*item, Gtk::PACK_SHRINK);
        break;
    }
}



// set the background color of the statusbar item
template <typename StatusType>
void StatusMulti<StatusType>::background(std::string background) {
    Gdk::RGBA color(background);
    item->override_background_color(color, Gtk::STATE_FLAG_NORMAL);
}



// Set the foreground color of the statusbar item
template <typename StatusType>
void StatusMulti<StatusType>::foreground(std::string foreground) {
    Gdk::RGBA color(foreground);
    item->override_color(color, Gtk::STATE_FLAG_NORMAL);
}
