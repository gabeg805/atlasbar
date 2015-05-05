// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     frame.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/frame.h"
// 
// 
// PURPOSE:
// 
//     Creates the frame that is just the bar, for the entire status bar.
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg Nov 06 2014 <> created
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/frame.h"
#include "../hdr/atlas.h"
#include "../hdr/util.h"
#include <gtk/gtk.h>

#define XPOS 0
#define YPOS 0

// Declares
void display_frame();



// ////////////////////////////////////
// ///// DISPLAY STATUS BAR FRAME /////
// ////////////////////////////////////

// Display status bar frame
void display_frame() {
    
    // Initialize taskbar items
    GtkWidget *win = gtk_window_new(GTK_WINDOW_POPUP);
    GtkWidget *bar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    
    // Setup widgets
    int pos[4] = {0, 0, 1366, 20};
    setup_widget(win, bar, pos);
    
    // Display widgets
    gtk_widget_show(bar);
    gtk_widget_show(win);
}
