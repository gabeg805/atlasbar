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


// Declares
void setup_window(GtkWidget *window, GtkWidget *bar);
void set_style();

PangoAttrList *attrList;
GdkRGBA color = {0.19, 0.19, 0.23, 1};



// //////////////////////////////////
// ///// SETUP STATUSBAR WINDOW /////
// //////////////////////////////////

// Setup gbar root window
void setup_window(GtkWidget *window, GtkWidget *bar) {
    
    // Get screen resolution
    Display* display = XOpenDisplay(NULL);
    Screen*  screen = DefaultScreenOfDisplay(display);
    int width  = screen->width;
    
    // Set window attributes
    gtk_window_move(GTK_WINDOW(window), 0, 0);
    gtk_window_set_default_size(GTK_WINDOW(window), width, 20);
    gtk_widget_override_background_color(window, GTK_STATE_NORMAL, &color);
    
    // GTK signal
    gtk_container_add(GTK_CONTAINER(window), bar);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}



// Setup font attributes for text on the statusbar
void set_style() {
    
    // Define text attributes
    char *font = "Inconsolata";
    int fsize  = 8*1024;
    
    attrList = pango_attr_list_new();
    PangoAttribute *attrFont = pango_attr_family_new(font);
    PangoAttribute *attrSize = pango_attr_size_new(fsize);
    PangoAttribute *attrColor = pango_attr_foreground_new(65535, 65535, 65535);
    
    // Add attributes to the list (and increase the reference counter)
    attrList = pango_attr_list_ref(attrList);
    attrList = pango_attr_list_ref(attrList);
    pango_attr_list_insert(attrList, attrSize);
    pango_attr_list_insert(attrList, attrFont);
    pango_attr_list_insert(attrList, attrColor);
}



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
        
        // Initialize gtk toolkit
        gtk_init(&argc, &argv);
        
        // Initialize taskbar items
        GtkWidget *window = gtk_window_new(GTK_WINDOW_POPUP);
        GtkWidget *bar    = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        
        // Setup widgets
        setup_window(window, bar);
        set_style();
        
        // Display widgets
        display_date(bar, attrList);    
        display_battery(bar);
        display_wifi(bar);
        display_volume(bar);
        display_brightness(bar);
        display_tags(bar, attrList, atoi(argv[1]));
        
        gtk_widget_show(bar);
        gtk_widget_show(window);
        
        // Kill previous invocations of gbar
        kill_gbar();
        
        // Run the gtk loop
        gtk_main();
        
        return 0;
    }
    
    return 0;
}
