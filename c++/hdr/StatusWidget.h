// -*-c++-*-

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
    
    // Status bar alignment
    enum Section { ALIGN_LEFT=1, ALIGN_CENTER, ALIGN_RIGHT };
    
    // Application
    template <typename atlas_w> 
    static void           attach(Gtk::Box *box, atlas_w *widg, StatusWidget::Section section);
    
    // Styling
    template <typename atlas_w> 
    static void           background(atlas_w *widg, std::string background);
    
    template <typename atlas_w>
    static void           foreground(atlas_w *widg, std::string foreground);
    
    template <typename atlas_w>
    static void           padding(atlas_w *widg, int x, int y);
    
    static void           font(Gtk::Label *label, std::string font, int size);
    
    // Utility
    static std::string    command(std::string cmd);
    static int            percent(std::string cmd);
};



// ///////////////////////
// ///// APPLICATION /////
// ///////////////////////

// Set the region of the statusbar to display the item (left/center/right);
template <typename atlas_w> 
void StatusWidget::attach(Gtk::Box *box, atlas_w *widg, StatusWidget::Section section) {
    if ( section == StatusWidget::ALIGN_LEFT )
        box->pack_start(*widg->item, Gtk::PACK_SHRINK);
    
    if ( section == StatusWidget::ALIGN_CENTER)
        box->set_center_widget(*widg->item);
    
    if ( section == StatusWidget::ALIGN_RIGHT)
        box->pack_end(*widg->item, Gtk::PACK_SHRINK);
}



// /////////////////
// ///// STYLE /////
// /////////////////

// set the background color of the statusbar item
template <typename atlas_w>
void StatusWidget::background(atlas_w *widg, std::string background) {
    Gdk::RGBA color(background);
    widg->item->override_background_color(color, Gtk::STATE_FLAG_NORMAL);
}



// Set the foreground color of the statusbar item
template <typename atlas_w>
void StatusWidget::foreground(atlas_w *widg, std::string foreground) {
    Gdk::RGBA color(foreground);
    widg->item->override_color(color, Gtk::STATE_FLAG_NORMAL);
}



// Set the statusbar item with the given font and size
template <typename atlas_w>
void StatusWidget::padding(atlas_w *widg, int x, int y) {
    widg->item->set_padding(x, y);
}



// Set the statusbar item with the given font and size
inline void StatusWidget::font(Gtk::Label *label, std::string font, int size) {
    Pango::FontDescription desc;
    desc.set_family(font);
    desc.set_size(size * PANGO_SCALE);
    
    label->override_font(desc);
}



// ///////////////////
// ///// UTILITY /////
// ///////////////////

// Return program command as a percent 
inline std::string StatusWidget::command(std::string cmd) {
        
    // Open up process
    char buf[256];
    std::string output;
    FILE *handle = popen(cmd.c_str(), "r");
        
    if ( handle == 0 ) 
        return "Atlas command fail.";
        
    // Get output from command
    while ( fgets(buf, sizeof(buf), handle) != 0 )
        output += buf;
        
    fclose(handle);
        
    return output;
}



// Return program command as a percent 
inline int StatusWidget::percent(std::string cmd) {
        
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

#endif
