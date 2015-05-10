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
//     #include "StatusMulti.h"
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
#include "../hdr/StatusMulti.h"
#include "../hdr/StatusSimple.h"
#include "../hdr/Statusbar.h"

#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>



// ////////////////////////
// ///// CONSTRUCTORS /////
// ////////////////////////

// Construct a container for multiple status bar items
template <typename atlas_w>
StatusMulti<atlas_w>::StatusMulti(Gtk::Orientation opt) {
    item = Gtk::manage( new Gtk::Box(opt) ); 
}



// ///////////////////////
// ///// APPLICATION /////
// ///////////////////////

// Fill up multi item statusbar application 
template <typename atlas_w>
void StatusMulti<atlas_w>::populate(std::vector<std::string> arr) {
    
    // Multi item statusbar app (try with std::vector)
    child = new StatusSimple<atlas_w> *[arr.size()];
    
    // Setup each item in the multi item app
    std::vector<std::string>::iterator iter;
    index = 0;
    int i = 0;
    
    for ( iter = arr.begin(); iter != arr.end(); ++iter ) {
        child[i] = new StatusSimple<atlas_w>(*iter);
        
        if ( i == index )
            StatusWidget::background(child[i]->item, "#999999");
        else
            StatusWidget::background(child[i]->item, "#333333");
        
        StatusWidget::attach(item, child[i]->item, StatusWidget::ALIGN_LEFT);
        StatusWidget::padding(child[i]->item, 5, 0);
        
        ++i;
    }
    
}



// Fill up multi item statusbar application 
template <>
void StatusMulti<Gtk::Label>::populate(std::vector<std::string> arr, std::string font, int size) {
    populate(arr);
    
    // Setup each item in the multi item app
    int i;
    int len = arr.size();
    
    for ( i = 0; i < len; ++i ) {
        StatusWidget::font(child[i]->item, font, size);
    }
}



// Set a function to call when updating statusbar icon/label
template <typename atlas_w>
void StatusMulti<atlas_w>::call(int (*func)(int)) {
    updateCall = func;
}



// Interface to choose correct icon/label setter
template <typename atlas_w>
bool StatusMulti<atlas_w>::set(int num) {
    int loc = updateCall(num);
    
    StatusWidget::background(child[loc]->item,   "#999999");
    StatusWidget::background(child[index]->item, "#333333");
    
    index = loc;
    
    return true;
}
