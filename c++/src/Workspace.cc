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
StatusMulti<Gtk::Label> *Workspace::widget;



// ////////////////////////////
// ///// SCREEN TAG INDEX /////
// ////////////////////////////

// Return the index of the screen tag
int Workspace::screen(int id) {
    int i = 0;
    
    while ( id != 0 ) {
        id >>= 1;
        ++i;
    }
    
    return (i-1);
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
    std::string bg                = Config::fetch(Config::FILE, "workspace_background");
    std::string hl                = Config::fetch(Config::FILE, "workspace_highlight");
    std::vector<std::string> tags = Config::parse(line, ',');
    
    // Setup the workspace widget
    widget = new StatusMulti<Gtk::Label>(bg, hl, Gtk::ORIENTATION_HORIZONTAL);
    widget->populate( tags, font, atoi(size.c_str()) );
    widget->call(screen);
}
