// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     StatusSimple.cc
// 
// 
// SYNTAX: 
// 
//     #include "StatusSimple.h"
// 
// 
// PURPOSE:
// 
//     A container to initialize and hold one statusbar item.
// 
// 
// KEYWORDS:
// 
//     N/A
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
#include "../hdr/StatusSimple.h"
#include "../hdr/Statusbar.h"

#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>



// ////////////////////////
// ///// CONSTRUCTORS /////
// ////////////////////////

// Construct the status bar item with the given icon path/label
template <typename atlas_w>
StatusSimple<atlas_w>::StatusSimple(std::string str) {
    item = Gtk::manage( new atlas_w(str) ); 
}



// Construct the statusbar item with the given font
template <>
StatusSimple<Gtk::Label>::StatusSimple(std::string str, std::string font, int size) {
    item = Gtk::manage( new Gtk::Label(str) ); 
    StatusWidget::font(item, font, size);
}



// ///////////////////////
// ///// APPLICATION /////
// ///////////////////////

// Set a function to call when updating statusbar icon/label
template <typename StatusType>
void StatusSimple<StatusType>::call(std::string (*func)()) {
    updateCall = func;
}



// Try and see if you can store <int, int, int> in a variable
template <typename atlas_w>
void StatusSimple<atlas_w>::update(std::string (*func)(), int time) {
    typedef bool (StatusSimple::*statinfo)(atlas_w*);
    updateCall = func;
    
    sigc::slot<bool, atlas_w*> pack = 
        sigc::mem_fun(*this, static_cast<statinfo>(&StatusSimple::set));
    Glib::signal_timeout().connect_seconds(sigc::bind<atlas_w*>(pack, item), time);
}



// Default icon/label setter 
template <typename atlas_w>
bool StatusSimple<atlas_w>::set(atlas_w *orig) {
    return true;
}

// Set the icon for the statusbar image
template <>
inline bool StatusSimple<Gtk::Image>::set(Gtk::Image *orig) {
    item->set( updateCall() ); 
    return true;
}

// Set the label for the statusbar label
template <>
inline bool StatusSimple<Gtk::Label>::set(Gtk::Label *orig) {
    item->set_text( updateCall() ); 
    return true;
}

// Interface to choose correct icon/label setter
template <typename atlas_w>
bool StatusSimple<atlas_w>::set() {
    set(item);
    return true;
}



// Return program command as a percent 
template <typename atlas_w>
int StatusSimple<atlas_w>::percent(std::string cmd) {
    
    // Get output from command
    FILE *handle = popen(cmd.c_str(), "r");
    char output[20];
    fgets(output, sizeof(output), handle);    
    fclose(handle);
    
    // Conversion variables
    std::string temp;
    std::string level;
    int i = 0;
    
    // Convert command output to percent value
    while ( (output[i] != 0) ) {
        
        // A number from 0-9 found
        if ( (output[i] >= '0') && (output[i] <= '9') ) {
            
            temp += output[i];
            
            if ( atoi(temp.c_str()) > 100 )
                break;
            
            level = temp;
            
        } else
            if ( level.compare("") != 0 )
                break;
        
        ++i;
    }
    
    return atoi(level.c_str());
}
