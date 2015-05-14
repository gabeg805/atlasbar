// -*-c++-*-
// **********************************************************************************
// 
// Name:    StatusMulti.h
// Class:   <StatusMulti>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The tools to contruct a series of simple widgets (Image/Label) and
//              their container.
//              
// Notes: The setter is specific to Workspace, try and change this. Change the way,
//        it populates items, make it more flexible to set a region for each item.
// 
// **********************************************************************************

// ============
// Header Guard
// ============

#ifndef STATUSMULTI_H
#define STATUSMULTI_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <string>
#include <iostream>


// =======
// Classes
// =======

class StatusMulti {
public:
    
    // Class variables
    Gtk::Box*                    item;
    std::vector<StatusSimple>    multi;
    void                         (*updateCall)(int);
    StatusWidget::Section        alignment;
    
    
    // Construct the container to hold multiple widgets
    void init () { 
        item      = Gtk::manage( new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL) ); 
        alignment = StatusWidget::ALIGN_LEFT;
    }
    
    // Construct the container to hold multiple widgets
    void init (StatusWidget::Section sec) { 
        item      = Gtk::manage( new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL) ); 
        alignment = sec;
    }
    
    
    
    
    // Set the orientation of the Multi container
    void orientation(Gtk::Orientation opt) { 
        StatusWidget::orientation(item, opt); 
    }
    
    
    
    // Set the orientation of the Multi container
    void align(StatusWidget::Section sec) { 
        alignment = sec;
    }
    
    
    
    // Add each widget to the container
    template <typename atlas_w>
    void populate(std::vector<std::string> arr) {
        std::vector<std::string>::iterator iter;
        
        for ( iter = arr.begin(); iter != arr.end(); ++iter ) {
            StatusSimple ss;
            ss.init <atlas_w> (*iter);
            
            multi.push_back(ss);
            
            StatusWidget::attach(item, ss, alignment);
            StatusWidget::padding((atlas_w*)ss.item, 5, 0);
        }
    }
    
    
    
    // Fill up multi item statusbar application 
    void populate(std::vector<std::string> arr, std::string fnt, int size) {
        populate <Gtk::Label> (arr);
        font(fnt, size);
    }
    
    
    
    // Set the font and text size for label widgets
    void font(std::string font, int size) {
        std::vector<StatusSimple>::iterator iter;
        
        for ( iter = multi.begin(); iter != multi.end(); ++iter ) 
            StatusWidget::font((Gtk::Label*)(*iter).item, font, size);
    }
    
    
    
    // Set the function to call periodically
    void call(void (*func)(int)) { 
        updateCall = func; 
    }
    
    
    
    // Set the correct icon/label through the specified periodic function
    bool set(int num) {
        updateCall(num);
        return true;
    }
};

#endif
