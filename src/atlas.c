// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     atlas.c
// 
// 
// SYNTAX: 
// 
//     $ gcc -o atlas *DEPENDENCIES.c -lX11 `pkg-config gtk+-3.0 --cflags --libs`
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
// FUNCTIONS:
// 
//     setup_window - Setup the statusbar window
//     set_style    - Setup the font attributes for text on the statusbar
//     main         - Display the ATLAS statusbar
// 
// 
// FILE STRUCTURE:
// 
//     * Includes and Declares
//     * Setup Statusbar Window
//     * Display ATLAS Statusbar
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
#include "../hdr/atlas.h"
#include "../hdr/util.h"
#include "../hdr/frame.h"
#include "../hdr/bat.h"
#include "../hdr/bright.h"
#include "../hdr/date.h"
#include "../hdr/vol.h"
#include "../hdr/tags.h"
#include "../hdr/wifi.h"

#include <gtk/gtk.h>
#include <X11/Xlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


// Declares
PangoAttrList *attrList;



// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////


// Display the atlas statusbar
int main(int argc, char **argv) {
    
    // Enable multi threading
    XInitThreads();
    
    // Initialize gtk toolkit
    gtk_init(&argc, &argv);
    
    // Setup widgets
    set_style();
    
    // Display widgets
    display_frame();
    display_tags(1);
    display_date(attrList);
    display_battery();
    display_wifi();
    display_volume();
    display_brightness();
    
    signal(SIGUSR1, widget_updater);
    
    // Run the gtk loop
    gtk_main();
    
    return 0;    
}
