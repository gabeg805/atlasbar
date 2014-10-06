// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     bright.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/bright.h"
// 
// 
// PURPOSE:
// 
//     Creates a brightness icon widget on the main status bar. Displays 
//     brightness level as a sun that fills up as the brightness increases.
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// FUNCTIONS:
// 
//     get_brightness      - Return current brightness level
//     get_brightness_icon - Return the proper brightness icon, given the  
//                           current brightness level
//     
//     set_brightness_icon - Set the brightness icon
//     
//     display_brightness  - Display the brightness widget
// 
// 
// FILE STRUCTURE:
// 
//     * Get Brightness Attributes
//     * Set Brightness Icon
//     * Display Brightness Widget
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
#include "../hdr/bright.h"
#include "../hdr/util.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define   ICON_DIR          "/home/gabeg/.config/awesome/img/icons/bright/"
#define   ICON_EXT          ".png"
#define   BRIGHT_NOW_FILE   "/sys/class/backlight/intel_backlight/brightness"
#define   BRIGHT_MAX_FILE   "/sys/class/backlight/intel_backlight/max_brightness"


// Declares
int get_brightness();
char * get_brightness_icon();
gboolean set_brightness_icon(gpointer data);
void display_brightness(GtkWidget *bar);



// /////////////////////////////////////
// ///// GET BRIGHTNESS ATTRIBUTES /////
// /////////////////////////////////////

// Return current brightness level
int get_brightness() {
    
    // Initialize file handler
    FILE *handle;
    
    // Get contents of NOW file
    handle = fopen(BRIGHT_NOW_FILE, "r");
    char bright_now[10];
    fgets(bright_now, sizeof(bright_now), handle);    
    fclose(handle);
    
    // Get contents of FULL file
    handle = fopen(BRIGHT_MAX_FILE, "r");
    char bright_max[10];
    fgets(bright_max, sizeof(bright_max), handle);    
    fclose(handle);
    
    // Calculate charge
    int now = atoi(bright_now);
    int full = atoi(bright_max);
    int bright = 100.0f * now / full;
    
    return bright;
}



// Return the proper brightness icon
char * get_brightness_icon() {
    
    // Initialize variables
    int level = get_brightness();    
    char *name;
    
    // Determine the correct brightness icon
    if ( (level >= 0) && (level <= 15) )
        name = "bright0-15";
    else if ( (level > 15) && (level <= 30) )
        name = "bright15-30";
    else if ( (level > 30) && (level <= 45) )
        name = "bright30-45";
    else if ( (level > 45) && (level <= 60) )
        name = "bright45-60";
    else if ( (level > 60) && (level <= 75) )
        name = "bright60-75";
    else if ( (level > 75) && (level <= 100) )
        name = "bright75-100";
    else {
        fprintf(stderr, "%s '%d'\n", "ERROR: Could not match level", level);
        name = "bright75-100";
    }
    
    
    // Allocate memory for string
    size_t sz = strlen(ICON_DIR) + strlen(name) + strlen(ICON_EXT) + 1;
    char *output = malloc(sz);
    snprintf(output, sz, "%s%s%s", ICON_DIR, name, ICON_EXT);
    
    return output;
}



// ///////////////////////////////
// ///// SET BRIGHTNESS ICON /////
// ///////////////////////////////

// Update the brightness widget
gboolean set_brightness_icon(gpointer data) {    
    
    // Extract widget from pointer
    GtkWidget *widget = (GtkWidget *) data;
    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    
    // Set icon onto widget
    char *bright_icon = get_brightness_icon();
    gtk_image_set_from_file(GTK_IMAGE(children->data), bright_icon);
    
    // Free memory
    free(bright_icon);
    g_list_free(children);
    
    return TRUE;
} 



// /////////////////////////////////////
// ///// DISPLAY BRIGHTNESS WIDGET /////
// /////////////////////////////////////

// Display the brightness widget
void display_brightness(GtkWidget *bar) {
    
    // Initialize brightness widget
    GtkWidget *bright = gtk_image_new();     
        
    // Set brightness icon
    char *bright_icon = get_brightness_icon();
    gtk_image_set_from_file(GTK_IMAGE(bright), bright_icon);
    
    // Enable events on volume widget
    widget_event(bar, bright, 0, set_brightness_icon);
}
