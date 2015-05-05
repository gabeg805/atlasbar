// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     atlas.cpp
// 
// 
// SYNTAX: 
// 
//     $ g++ -o atlas *DEPENDENCIES.c `pkg-config gtk+-3.0 --cflags --libs`
// 
// 
// PURPOSE:
// 
//     Creates a taskbar at the top of the screen that contains:
//         
//         - Workspace tags
//         - Date and time
//         - Screen brightness
//         - Volume level
//         - Wifi strength
//         - Battery charge level
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg Sep 16 2014 <> created
// 
//     gabeg Sep 16 2014 <> Moved functions to update the statusbar over to "util.c"
//                          and added comments to each function
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/StatusBar.h"
#include "../hdr/Battery.h"
#include "../hdr/Wifi.h"
#include "../hdr/Volume.h"
#include "../hdr/Brightness.h"
#include "../hdr/Date.h"
#include "../hdr/Workspace.h"
#include "../hdr/util.h"

#include <gtkmm.h>
#include <iostream>
#include <cstdlib>
#include <signal.h>

using namespace std;



// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

// LOOK AT GTKMM ONLINE
// https://developer.gnome.org/gtkmm-tutorial/stable/sec-basics-simple-example.html.en

Battery    *battery;
Wifi       *wifi;
Volume     *volume;
Brightness *brightness;
Date       *date;
Workspace  *workspace;

// Display the atlas statusbar
int main(int argc, char *argv[]) {
    
    // Initialize gtkmm application
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");
    
    // Setup statusbar
    StatusBar  Atlas;
    workspace = new Workspace();
    
    battery->display(&Atlas.bar);
    wifi->display(&Atlas.bar);
    volume->display(&Atlas.bar);
    brightness->display(&Atlas.bar);
    date->display(&Atlas.bar);
    workspace->display(&Atlas.bar);
    
    Atlas.show_all_children();
    
    signal(SIGUSR1, widget_updater);
    
    return app->run(Atlas);
}
