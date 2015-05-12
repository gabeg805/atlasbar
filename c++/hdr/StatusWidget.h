// -*-c++-*-
// **********************************************************************************
// 
// Name:    StatusWidget.h
// Class:   <StatusWidget>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: Contains the standard utility functionality for each widget.
//              
// Notes: None.
// 
// **********************************************************************************


// ============
// Header Guard
// ============

#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H


// ========
// Includes
// ========

#include <gtkmm.h>
#include <gdkmm.h>
#include <pangomm/fontdescription.h>
#include <stdio.h>
#include <string>



// =======
// Classes
// =======

class StatusWidget {
public:
    
    // Widget alignment within the container 
    enum Section { ALIGN_LEFT=1, ALIGN_CENTER, ALIGN_RIGHT };
    
    
    
    // Attach the widget onto the container in the given region
    template <typename atlas_w> 
    static void attach(Gtk::Box* box, atlas_w* widg, StatusWidget::Section section) {
        if ( section == StatusWidget::ALIGN_LEFT )
            box->pack_start(*widg->item, Gtk::PACK_SHRINK);
        
        if ( section == StatusWidget::ALIGN_CENTER)
            box->set_center_widget(*widg->item);
        
        if ( section == StatusWidget::ALIGN_RIGHT)
            box->pack_end(*widg->item, Gtk::PACK_SHRINK);
    }
    
    
    
    // Set the horizontal and vertical padding of the widget
    template <typename atlas_w>
    static void padding(atlas_w* widg, int x, int y) {
        widg->set_padding(x, y);
    }
    
    
    
    // Set the background color of the widget
    template <typename atlas_w>
    static void background(atlas_w* widg, std::string background) {
        Gdk::RGBA color(background);
        widg->override_background_color(color, Gtk::STATE_FLAG_NORMAL);
    }
    
    
    
    // Set the foreground color of the widget
    template <typename atlas_w>
    static void foreground(atlas_w* widg, std::string foreground) {
        Gdk::RGBA color(foreground);
        widg->override_color(color, Gtk::STATE_FLAG_NORMAL);
    }
    
    
    
    // Set the font and text size of the widget
    static void font(Gtk::Label* label, std::string font, int size) {
        Pango::FontDescription desc;
        desc.set_family(font);
        desc.set_size(size * PANGO_SCALE);
        
        label->override_font(desc);
    }
    
    
    
    // Return the program command output as a percent 
    static std::string command(std::string cmd) {
        
        // Open up process
        char buf[256];
        std::string output;
        FILE* handle = popen(cmd.c_str(), "r");
        
        if ( handle == 0 ) 
            return "Atlas command fail.";
        
        // Get output from command
        while ( fgets(buf, sizeof(buf), handle) != 0 )
            output += buf;
        
        fclose(handle);
        
        return output;
    }
    
    
    
    // Return the program command output as a percent
    static int percent(std::string cmd) {
        
        // Prepare to convert command output
        std::string level;
        std::string output = command(cmd);
        
        // Convert command output to percent value
        for ( size_t i = 0; i < output.length(); ++i ) {
            
            // A number from 0-9 found
            if ( (output[i] >= '0') && (output[i] <= '9') ) {
                
                // Stop when three digit number (excluding 100)
                if ( (level.length() == 2) ) {
                    if ( (level.compare("10") == 0) && (output[i] == '0') ) 
                        ;
                    else
                        break;
                }
                
                level += output[i];
            } else
                if ( level.compare("") != 0 )
                    break;
        }
        
        return atoi( level.c_str() );
    }
};

#endif
