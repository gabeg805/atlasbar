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
//     $ g++ -g -Wall `pkg-config gtkmm-3.0 --cflags --libs` src/*.cc -o atlas
//     $ ./atlas
// 
// 
// PURPOSE:
// 
//     Creates a statusbar at the top of the screen that contains:
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
//     gabeg May 02 2015 <> Created.
// 
//     gabeg May 07 2015 <> Finished converting the C implementation to C++.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/StatusBar.hpp"
#include "../hdr/StatusWatcher.hpp"
#include "../hdr/Battery.hpp"
#include "../hdr/Wifi.hpp"
#include "../hdr/Volume.hpp"
#include "../hdr/Brightness.hpp"
#include "../hdr/Date.hpp"
#include "../hdr/Workspace.hpp"

#include <gtkmm.h>
#include <csignal>



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
        
    battery->display(&Atlas.bar);
    wifi->display(&Atlas.bar);
    volume->display(&Atlas.bar);
    brightness->display(&Atlas.bar);
    date->display(&Atlas.bar);
    workspace->display(&Atlas.bar);
    
    Atlas.show_all_children();
    
    signal(SIGUSR1, statusWatcher);
    
    return app->run(Atlas);
}
