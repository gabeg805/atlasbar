// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     StatusItem.cc
// 
// 
// SYNTAX: 
// 
//     #include "StatusItem.h"
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
#include "../hdr/StatusItem.h"
#include "../hdr/StatusBar.h"

#include <gtkmm.h>
#include <pangomm/fontdescription.h>
#include <cstdlib>
#include <iostream>
#include <string>



// ////////////////////////
// ///// CONSTRUCTORS /////
// ////////////////////////

// Default empty constructor
template <typename StatusType>
StatusItem<StatusType>::StatusItem() {
}



// Construct the status bar item with the given icon path/label
template <typename StatusType>
StatusItem<StatusType>::StatusItem(std::string str) {
    item = Gtk::manage( new StatusType(str) ); 
}



// Construct statusbar item with the given font
template <>
StatusItem<Gtk::Label>::StatusItem(std::string str, std::string font, int size) {
    item = Gtk::manage( new Gtk::Label(str) ); 
    
    Pango::FontDescription desc;
    desc.set_family(font);
    desc.set_size(size * PANGO_SCALE);
    
    item->override_font(desc);
}



// ///////////////////////
// ///// APPLICATION /////
// ///////////////////////

// Return program command as a percent 
template <typename StatusType>
int StatusItem<StatusType>::percent(std::string cmd) {
    
    // Get output from command
    FILE *handle = popen(cmd.c_str(), "r");
    char output[20];
    fgets(output, sizeof(output), handle);    
    fclose(handle);
    
    // Convert command output to integer volume level
    std::string level;
    bool found = false;
    int i      = 0;
    
    while ( (output[i] != 0) ) {
        
        if ( (output[i] >= '0') && (output[i] <= '9') ) {
            found = true;
            level += output[i];
            
            if ( atoi(level.c_str()) > 100 )
                break;
        } else
            if ( found == true )
                break;
        
        ++i;
    }
    
    return atoi(level.c_str());
}



// Set a function to call when updating statusbar icon/label
template <typename StatusType>
void StatusItem<StatusType>::call(std::string (*func)()) {
    updateCall = func;
}



// Try and see if you can store <int, int, int> in a variable
template <typename StatusType>
void StatusItem<StatusType>::update(std::string (*func)(), int time) {
    typedef bool (StatusItem::*uglyass)(StatusType*);
    updateCall = func;
    
    // sigc::slot<bool, StatusType*, string(*)()> pack = 
    //     sigc::mem_fun(*this, static_cast<uglyass>(&StatusItem::timeout));
    // Glib::signal_timeout().connect_seconds(sigc::bind<StatusType*, string(*)()>(pack, item, func), time);
    
    sigc::slot<bool, StatusType*> pack = 
        sigc::mem_fun(*this, static_cast<uglyass>(&StatusItem::set));
    Glib::signal_timeout().connect_seconds(sigc::bind<StatusType*>(pack, item), time);
}



// Default icon/label setter 
template <typename StatusType>
bool StatusItem<StatusType>::set(StatusType *orig) {
    return true;
}



// Set the icon for the statusbar image
template <>
inline bool StatusItem<Gtk::Image>::set(Gtk::Image *orig) {
    item->set( updateCall() ); 
    return true;
}



// Set the label for the statusbar label
template <>
inline bool StatusItem<Gtk::Label>::set(Gtk::Label *orig) {
    item->set_text( updateCall() ); 
    return true;
}



// Interface to choose correct icon/label setter
template <typename StatusType>
bool StatusItem<StatusType>::set() {
    set(item);
    return true;
}



// ///////////////////
// ///// STYLING /////
// ///////////////////

// Set the region of the statusbar to display the item (left/center/right);
template <typename StatusType>
void StatusItem<StatusType>::attach(Gtk::Box *bar, StatusBar::Section sec) {
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



// Set the background color of the statusbar item
template <typename StatusType>
void StatusItem<StatusType>::background(std::string background) {
    Gdk::RGBA color(background);
    item->override_background_color(color, Gtk::STATE_FLAG_NORMAL);
}



// Set the foreground color of the statusbar item
template <typename StatusType>
void StatusItem<StatusType>::foreground(std::string foreground) {
    Gdk::RGBA color(foreground);
    item->override_color(color, Gtk::STATE_FLAG_NORMAL);
}



// Construct statusbar item with the given font
template <>
void StatusItem<Gtk::Label>::font(std::string font, int size) {
    Pango::FontDescription desc;
    desc.set_family(font);
    desc.set_size(size * PANGO_SCALE);
    
    item->override_font(desc);
}
