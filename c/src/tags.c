// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     tags.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/tags.h"
// 
// 
// PURPOSE:
// 
//     Creates a tags widget on the main status bar that displays the tags in 
//     the format: "Sun Oct 5, 12:48 PM".
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// FUNCTIONS:
// 
//     exponent      - Calculate the exponent of a value, 
//                     i.e. exponent(2, 3) = 8
//     get_tag       - Get the tag value. Tags come in powers of two, 
//                     i.e. tag 3 has a value of 8
//     
//     display_tags  - Display the tags widget
// 
// 
// FILE STRUCTURE:
// 
//     * Includes and Declares
//     * Get Tag Attributes
//     * Display Tag Widget
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg Sep 15 2014 <> created
// 
//     gabeg Oct 05 2014 <> Added a header to the source file.
// 
//     gabeg Nov 02 2014 <> Made it so that the tags widget did not have to rely on 
//                          the Atlas frame (being passed in as a parameter). 
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/tags.h"
#include "../hdr/atlas.h"
#include "../hdr/util.h"
#include <gtk/gtk.h>
#include <stdlib.h>

#define XPOS       0
#define YPOS       0
#define PADDING    5


// Declares
int CSCALE = 65535 / 255;
GdkRGBA colores = {0.62, 0.62, 0.62, 1};



// ////////////////////////////
// ///// SCREEN TAG INDEX /////
// ////////////////////////////

// Return the index of the screen tag
static int get_screen(int loc) {
    int i = 0;
    
    while ( loc != 0 ) {
        loc >>= 1;
        ++i;
    }
    
    return (i-1);
}



// ///////////////////////////////
// ///// DISPLAY TAGS WIDGET /////
// ///////////////////////////////

// Display the tags widget
void display_tags(int loc) {
    
    // Initialize widget window
    GtkWidget *win    = gtk_window_new(GTK_WINDOW_POPUP);
    GtkWidget *holder = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    
    // Tag loop parameters
    int i = 0;
    char *tags[] = {"1", "2", "3", "4", "5", NULL};
    
    // Create all tags
    while ( tags[i] != NULL ) {
        
        // Initialize tag widget
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        GtkWidget *tag = gtk_label_new(tags[i]);
        
        // Highlight current tag
        gtk_label_set_attributes(GTK_LABEL(tag), attrList);
        
        if ( i == get_screen(loc) ) 
            gtk_widget_override_background_color(box, GTK_STATE_NORMAL, &colores);
        
        // Add tags to widget
        gtk_box_pack_start(GTK_BOX(box),    tag, 0, 0, PADDING);
        gtk_box_pack_start(GTK_BOX(holder), box, 0, 0, 0);
        
        // Display tags
        gtk_widget_show(tag);
        gtk_widget_show(box);
        
        ++i;
    }
    
    // Setup widget
    int pos[4] = {XPOS, YPOS, 0, 20};
    setup_widget(win, holder, pos);
    
    // Display widgets
    gtk_widget_show(holder);
    gtk_widget_show(win);
}
