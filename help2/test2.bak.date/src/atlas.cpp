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
// #include "../hdr/bat.h"
// #include "../hdr/bright.h"
#include "../hdr/date.h"
// #include "../hdr/vol.h"
// #include "../hdr/tags.h"
// #include "../hdr/wifi.h"

#include <gtkmm.h>
// #include <gtk/gtk.h>
// #include <signal.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>


// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

// LOOK AT GTKMM ONLINE
// https://developer.gnome.org/gtkmm-tutorial/stable/sec-basics-simple-example.html.en

// Display the atlas statusbar
int main(int argc, char *argv[]) {
    
    // Initialize gtkmm application
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");
    
    // Setup statusbar
    StatusBar Atlas;
    display_date(&Atlas.bar);
    
    Atlas.show_all_children();
    return app->run(Atlas);
    // return Atlas.run(app);
    // Atlas.init();
    
    
    // Setup widgets
    // Atlas.init();
    
    // // Display widgets
    // display_tags(1);
    // display_date();
    // display_battery();
    // display_volume(); // Switch this and below
    // display_wifi();
    // display_brightness();
    
    // gtk_widget_show(Atlas.bar);
    // gtk_widget_show(Atlas.win);
    
    // // signal(SIGUSR1, widget_updater);
    
    // // Run the gtk loop
    // gtk_main();
    
    return 0;
}
