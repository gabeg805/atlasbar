// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     gbar.c
// 
// 
// SYNTAX: 
// 
//     $ gcc -o gbar *DEPENDENCIES.c -lX11 `pkg-config gtk+-3.0 --cflags --libs`
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
//     main         - Display the GBAR statusbar
// 
// 
// FILE STRUCTURE:
// 
//     * Includes and Declares
//     * Setup Statusbar Window
//     * Display GBAR Statusbar
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
#include "../hdr/globals.h"
#include "../hdr/util.h"
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
#include <stdio.h>
#include <stdlib.h>

#define GBAR_LOG "/home/gabeg/.config/dwm/src/gbar/log/gbar.log"

// Declares

PangoAttrList *attrList;
GdkRGBA color = {0.19, 0.19, 0.23, 1};
int screen_width;
int bar_height;



// //////////////////////////////////
// ///// DISPLAY GBAR STATUSBAR /////
// //////////////////////////////////

// Display the gbar statusbar
int main(int argc, char**argv) {
    
    // Clean up zombie processes
    signal(SIGCHLD, cleanup_child);
    
    // Enable multi threading
    XInitThreads();
    
    // Create the bar
    pid_t pid = fork();
    if ( pid == 0 ) {
        
        // Get screen resolution
        Display* display = XOpenDisplay(NULL);
        Screen*  screen = DefaultScreenOfDisplay(display);
        screen_width  = screen->width;
        bar_height = 20;
        
        // Initialize gtk toolkit
        gtk_init(&argc, &argv);
        
        // Initialize taskbar items
        GtkWidget *window = gtk_window_new(GTK_WINDOW_POPUP);
        GtkWidget *bar    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        
        // Setup widgets
        setup_window(window, bar);
        set_style();
        
        // Display widgets
        gtk_widget_show(bar);
        gtk_widget_show(window);

        display_tags(atoi(argv[1]));
        display_date(attrList);
        display_battery();
        display_wifi();
        display_volume();
        display_brightness();
        
        // Write PID to file
        file_write(GBAR_LOG, "w", "%d", getpid());
        
        // Run the gtk loop
        gtk_main();
        
        return 0;
    }
    
    kill_gbar();
    remove(GBAR_LOG);
    
    return 0;
}
