// -*-c++-*-
// **********************************************************************************
// 
// Name:    Workspace.h
// Class:   <Workspace>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: The Workspace widget skeleton.
//              
// Notes: Member variables are static, try and find a way around this.
// 
// **********************************************************************************

// ============
// Header Guard
// ============

#ifndef WORKSPACE_H
#define WORKSPACE_H


// ========
// Includes
// ========

#include "../hdr/StatusMulti.h"

#include <gtkmm.h>


// =======
// Classes
// =======

class Workspace {
public:
    
    // Determines the array index of the given workspace.
    static void                        screen(int ws);
    
    // Creates a new widget.
    void                               create();
    
    // Container for the widget.
    static StatusMulti*                widget;
    
private:
    
    // Workspace labels
    static std::vector<std::string>    tags;
    
    // Workspace colors
    static std::string                 background;
    static std::string                 highlight;
};


// Declares
extern Workspace* workspace;

#endif
