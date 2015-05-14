// -*-c++-*-
// **********************************************************************************
// 
// Name:    Wifi.h
// Class:   <Wifi>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The Wifi widget skeleton.
//              
// Notes: None.
// 
// **********************************************************************************


// ============
// Header Guard
// ============

#ifndef WIFI_H
#define WIFI_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Wifi {
 public:
    
    // Determines the correct icon for the widget and sets it as the widget icon.
    static std::string     icon();
    
    // Creates a new widget.
    void                   create();
    
    // Container for the widget.
    static StatusSimple    widget;
};


// Declares
extern Wifi wifi;

#endif
