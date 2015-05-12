// **********************************************************************************
// 
// Name:    Workspace.cc
// Class:   <Workspace>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: A workspace indicator. Each workspace is given a name (via the config  
//              file), and the current workspace is highlighted.
//              
// Notes: None.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Workspace.h"
#include "../hdr/StatusMulti.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <string>
#include <vector>

// Declares
StatusMulti*                Workspace::widget;
std::string                 Workspace::background;
std::string                 Workspace::highlight;
std::vector<std::string>    Workspace::tags;



// ////////////////////////////
// ///// SCREEN TAG INDEX /////
// ////////////////////////////

// Return the index of the screen tag
void Workspace::screen(int ws) {
    size_t index;
    size_t loc = 0;
    
    // Determine the index of the workspace to highlight
    while ( (ws >>= 1) != 0 ) { ++loc; }
    
    // Highlight the specified workspace    
    for ( index = 0; index < tags.size(); ++index ) {
        if ( index == loc )
            StatusWidget::background(widget->multi[index]->item, highlight);
        else
            StatusWidget::background(widget->multi[index]->item, background);
    }
}



// ///////////////////////////////
// ///// DISPLAY TAGS WIDGET /////
// ///////////////////////////////

// Display the tags widget
void Workspace::create() {
    
    // Read workspace tag labels from config file
    std::string line              = Config::fetch(Config::FILE, "workspace_tags");
    std::string font              = Config::fetch(Config::FILE, "workspace_font");
    std::string size              = Config::fetch(Config::FILE, "workspace_font_size");
    background                    = Config::fetch(Config::FILE, "workspace_background");
    highlight                     = Config::fetch(Config::FILE, "workspace_highlight");
    tags                          = Config::parse(line, ',');
    
    // Setup the workspace widget
    widget = new StatusMulti(Gtk::ORIENTATION_HORIZONTAL);
    widget->populate(tags, font, atoi(size.c_str()));
    widget->call(screen);
    screen(0);
}
