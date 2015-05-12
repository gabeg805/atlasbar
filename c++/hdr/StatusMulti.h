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
    typedef std::vector<std::string>    stdvec;
    Gtk::Box*                           item;
    StatusSimple**                      multi;
    void                                (*updateCall)(int);
    
    
    
    // Construct the container to hold multiple widgets
    StatusMulti(Gtk::Orientation opt) { 
        item = Gtk::manage( new Gtk::Box(opt) ); 
    }
    
    
    
    // Add each widget to the container
    template <typename atlas_w>
    void populate(stdvec arr) {
        stdvec::iterator iter;
        multi = new StatusSimple* [arr.size()];
        int i = 0;
        
        // Attach each widget to the multi container
        for ( iter = arr.begin(); iter != arr.end(); ++iter ) {
            multi[i] = new StatusSimple();
            multi[i]->init <atlas_w> (*iter);
            
            StatusWidget::attach(item, multi[i], StatusWidget::ALIGN_LEFT);
            StatusWidget::padding((atlas_w*)multi[i]->item, 5, 0);
            
            ++i;
        }
    }
    
    
    
    // Fill up multi item statusbar application 
    void populate(stdvec arr, std::string fnt, int size) {
        populate <Gtk::Label> (arr);
        font(fnt, size, arr.size());
    }
    
    
    
    // Set the font and text size for label widgets
    void font(std::string font, int size, size_t num) {
        size_t i;
        
        for ( i = 0; i < num; ++i ) 
            StatusWidget::font((Gtk::Label*)multi[i]->item, font, size);
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
