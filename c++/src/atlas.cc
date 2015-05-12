// **********************************************************************************
// 
// Name:    atlas.cc
// Class:   main()
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Syntax: $ g++ -g -Wall `pkg-config gtkmm-3.0 --cflags --libs` src/*.cc -o atlas
//         $ ./atlas
// 
// Description: Pieces together the statusbar unit, all the widgets for the
//              statusbar, and the signal catcher, in order to form a completed
//              statusbar.
//              
// Notes: None.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/StatusWidget.h"
#include "../hdr/Statusbar.h"

#include "../hdr/Battery.h"
#include "../hdr/Wifi.h"
#include "../hdr/Volume.h"
#include "../hdr/Brightness.h"
#include "../hdr/Date.h"
#include "../hdr/Workspace.h"

#include <gtkmm.h>

// Declares
Battery*    battery;
Wifi*       wifi;
Volume*     volume;
Brightness* brightness;
Date*       date;
Workspace*  workspace;



// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

// Display the atlas statusbar
int main(int argc, char** argv) {
    
    // Initialize gtkmm application
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");
    
    // Setup statusbar
    Statusbar  Atlas;
    
    Atlas.attach<Battery>(battery,       StatusWidget::ALIGN_RIGHT);
    Atlas.attach<Wifi>(wifi,             StatusWidget::ALIGN_RIGHT);
    Atlas.attach<Volume>(volume,         StatusWidget::ALIGN_RIGHT);
    Atlas.attach<Brightness>(brightness, StatusWidget::ALIGN_RIGHT);
    Atlas.attach<Date>(date,             StatusWidget::ALIGN_CENTER);
    Atlas.attach<Workspace>(workspace,   StatusWidget::ALIGN_LEFT);
    
    Atlas.show_all_children();    
    
    return app->run(Atlas);
}
