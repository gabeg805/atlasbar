// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     bat.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/bat.h"
// 
// 
// PURPOSE:
// 
//     Creates a battery icon widget on the main status bar. Displays battery
//     level as a circular icon that changes color (from green to yellow to red)
//     as the battery level decreases.
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
//     gabeg Nov 02 2014 <> Made it so that the battery widget did not have to rely 
//                          on the Atlas frame (being passed in as a parameter). 
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
#include "../hdr/bat.h"
#include "../hdr/util.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

// Declares
static void get_battery_icon(char *path);
static gboolean set_battery_icon(gpointer data);



// //////////////////////////////////
// ///// GET BATTERY ATTRIBUTES /////
// //////////////////////////////////

// Return the proper battery icon
static void get_battery_icon(char *path) {
    
    // Initialize variables
    char *icon_dir = "/home/gabeg/.config/awesome/img/icons/bat/bat";
    char *icon_suf = "-charge";
    char *icon_ext = ".png";
    char *cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/bat";
    int charge     = get_percent(cmd);
    
    // Determine the correct volume icon
    size_t sz  = 0;
    size_t sza = strlen(icon_dir) + strlen(icon_suf) + strlen(icon_ext) + 1;
    size_t szb = strlen(icon_dir) + sizeof(charge) + strlen(icon_ext) + 1;
    
    if ( charge == -1 ) 
        sz = sza;
    else 
        sz = szb;
    
    // Allocate memory for string
    if ( sz == sza )
        snprintf(path, sz, "%s%s%s", icon_dir, icon_suf, icon_ext);
    else
        snprintf(path, sz, "%s%d%s", icon_dir, charge, icon_ext);
}



// ////////////////////////////
// ///// SET BATTERY ICON /////
// ////////////////////////////

// Set the battery icon on the widget
static gboolean set_battery_icon(gpointer data) {
    
    // Extract widget from pointer
    GtkWidget *widget = (GtkWidget *) data;
    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    
    // Get icon location
    char path[256];
    get_battery_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(children->data), path);
    
    // Free memory
    g_list_free(children);
    
    return TRUE;
} 



// //////////////////////////////////
// ///// DISPLAY BATTERY WIDGET /////
// //////////////////////////////////

// Display the battery widget
void display_battery() {
    
    // Initialize widgets
    GtkWidget *bat = gtk_image_new();
    
    // Set widget icon
    char path[256];
    get_battery_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(bat), path);
    
    // Setup widget
    widget_mouse_enter(App.win, bat, 120, set_battery_icon);
    
    // Display widgets
    gtk_widget_show(bat);
}
