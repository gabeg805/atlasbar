// -*-c++-*-
// **********************************************************************************
// 
// Name:    Date.h
// Class:   <Date>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The Date widget skeleton.
//              
// Notes: None.
// 
// **********************************************************************************

// ============
// Header Guard
// ============

#ifndef DATE_H
#define DATE_H


// ========
// Includes
// ========

#include "../hdr/StatusSimple.h"

#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class Date {
 public:
    
    // Determines the current time.
    static std::string     now();
    
    // Creates a new widget.
    void                   create();
    
    // Container for the widget.
    static StatusSimple    widget;
};


// Declares
extern Date date;

#endif
