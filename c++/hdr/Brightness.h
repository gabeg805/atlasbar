// -*-c++-*-
// **********************************************************************************
// 
// Name:    Brightness.h
// Class:   <Brightness>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The Brightness widget skeleton.
//              
// Notes: None.
// 
// **********************************************************************************

// ============
// Header Guard
// ============

#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Brightness {
public:
    
    // Determines the correct icon for the widget and sets it as the widget icon.
    static std::string     icon();
    
    // Creates a new widget.
    void                   create();
    
    // Container for the widget.
    static StatusSimple    widget;
};


// Declares
extern Brightness brightness;

#endif
