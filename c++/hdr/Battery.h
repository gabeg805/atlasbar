// -*-c++-*-
// **********************************************************************************
// 
// Name:    Battery.h
// Class:   <Battery>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The Battery widget skeleton.
//              
// Notes: None.
// 
// **********************************************************************************

// ============
// Header Guard
// ============

#ifndef BATTERY_H
#define BATTERY_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Battery {
 public:
    
    // Determines the correct icon for the widget and sets it as the widget icon.
    static std::string      icon();
    
    // Creates a new widget.
    void                    create();
    
    // Container for the widget.
    static StatusSimple*    widget;
};


// Declares
extern Battery* battery;

#endif
