// -*-c++-*-
// **********************************************************************************
// 
// Name:    Volume.h
// Class:   <Volume>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The Volume widget skeleton.
//              
// Notes: None.
// 
// **********************************************************************************

// ============
// Header Guard
// ============

#ifndef VOLUME_H
#define VOLUME_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Volume {
 public:
    
    // Determines the correct icon for the widget and sets it as the widget icon.
    static std::string     icon();
    
    // Creates a new widget.
    void                   create();
    
    // Container for the widget.
    static StatusSimple    widget;
};


// Declares
extern Volume volume;

#endif
