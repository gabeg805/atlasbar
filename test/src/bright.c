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
// MODIFICATION HISTORY:
// 	
//     gabeg Sep 15 2014 <> created
// 
//     gabeg Oct 05 2014 <> Added a header to the source file.
// 
//     gabeg Nov 02 2014 <> Made it so that the brightness widget did not have to 
//                          rely on the Atlas frame (being passed in as a parameter). 
// 
//     gabeg May 02 2014 <> Removed excessive parts of the header.
//                          Made every widget attach to one Application, instead of 
//                          being separate entities.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/bright.h"
#include "../hdr/util.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

// Declares
static void get_brightness_icon(char *path);

static GtkWidget *bright_event;




// /////////////////////////////////////
// ///// GET BRIGHTNESS ATTRIBUTES /////
// /////////////////////////////////////

// Return the proper brightness icon
static void get_brightness_icon(char *path) {
    
    // Initialize variables
    char *icon_dir = "/home/gabeg/.config/awesome/img/icons/bright/";
    char *icon_ext = ".png";
    char *cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/bright";
    int level      = get_percent(cmd);
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
    size_t sz = strlen(icon_dir) + strlen(name) + strlen(icon_ext) + 1;
    snprintf(path, sz, "%s%s%s", icon_dir, name, icon_ext);
}



// ///////////////////////////////
// ///// SET BRIGHTNESS ICON /////
// ///////////////////////////////

// Update the brightness widget
gboolean set_brightness_icon(gpointer data) {
    
    // Extract widget from pointer
    /* GtkWidget *widget = (GtkWidget *) data; */
    GList *children = gtk_container_get_children(GTK_CONTAINER(bright_event));
    
    // Set icon onto widget
    char path[256];
    get_brightness_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(children->data), path);
    
    // Free memory
    g_list_free(children);
    
    return TRUE;
} 



// /////////////////////////////////////
// ///// DISPLAY BRIGHTNESS WIDGET /////
// /////////////////////////////////////

// Display the brightness widget
void display_brightness() {
    
    // Initialize brightness widget
    GtkWidget *bright = gtk_image_new();     
    
    // Set brightness icon
    char path[256];
    get_brightness_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(bright), path);
    
    // Setup widget
    /* widget_mouse_enter(App.win, bright, 0, set_brightness_icon); */
    bright_event = gtk_event_box_new();
    widget_mouse_entera(bright_event, App.win, bright, 0, set_brightness_icon);
    
    // Display widgets
    gtk_widget_show(bright);
}
