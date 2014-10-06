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
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/tags.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Declares
int exponent(int num, int power);
int get_tag(int screen);
void display_tags(GtkWidget *bar, PangoAttrList *attrList, int screen);

const char *dwm_tags[] = { "1", "2", "3", "4", "5" };
int CSCALE = 65535 / 255;
GdkRGBA colores = {0.62, 0.62, 0.62, 1};



// //////////////////////////////
// ///// GET TAG ATTRIBUTES /////
// //////////////////////////////

// Return a number raised to the given power
int exponent(int num, int power) {
    int i;
    int result = 1;
    for ( i = 0; i < power; ++i ) 
        result *= num;
    
    return result;
}



// Get the current tag (goes from 0...9)
int get_tag(int screen) {
        
    // Convert exponent to number
    int base = 2;
    int power = 0;
    
    while (power < 10) {
        if ( screen == exponent(base, power) )
            break;
        ++power;
    }
    
    return power;
}




// ///////////////////////////////
// ///// DISPLAY TAGS WIDGET /////
// ///////////////////////////////

// Display the tags widget
void display_tags(GtkWidget *bar, PangoAttrList *attrList, int screen) {
    
    // Tag loop parameters
    int length = sizeof(dwm_tags) / sizeof(dwm_tags[0]);
    int i;
    
    // Create all tags
    for ( i = 0; i < length; ++i ) {
        
        // Initialize tag widget
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        GtkWidget *tag = gtk_label_new(dwm_tags[i]);
        
        
        // Highlight current tag
        gtk_label_set_attributes(GTK_LABEL(tag), attrList);
        
        if ( i == get_tag(screen) ) 
            gtk_widget_override_background_color(box, GTK_STATE_NORMAL, &colores);
        
        // Add tags to widget
        gtk_box_pack_start(GTK_BOX(box), tag, 0, 0, 0);
        gtk_box_pack_start(GTK_BOX(bar), box, 0, 0, 0);
        
        // Display tags
        gtk_widget_show(tag);
        gtk_widget_show(box);
    }
}
