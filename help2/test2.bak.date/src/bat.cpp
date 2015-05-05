// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     bat.cpp
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
#include "../hdr/Statusbar.h"
#include "../hdr/bat.h"
#include "../hdr/util.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include <iostream>
#include <sstream>
#include <string>

// Declares
static std::string get_battery_icon();
static gboolean set_battery_icon(gpointer data);



// //////////////////////////////////
// ///// GET BATTERY ATTRIBUTES /////
// //////////////////////////////////

// Return the proper battery icon
static std::string get_battery_icon() {
    
    // Initialize variables
    std::string icon_dir = "/home/gabeg/.config/awesome/img/icons/bat/bat";
    std::string icon_suf = "-charge";
    std::string icon_ext = ".png";
    std::string cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/bat";
    int charge           = Atlas.get_percent(cmd);
    
    // Determine the correct volume icon
    std::stringstream ss;
    ss << charge;
    std::string path = icon_dir + ss.str() + icon_ext;
    
    return path;
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
    std::string path = get_battery_icon();
    gtk_image_set_from_file(GTK_IMAGE(children->data), path.c_str());
    
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
    std::string path = get_battery_icon();
    gtk_image_set_from_file(GTK_IMAGE(bat), path.c_str());
    
    // Setup widget
    widget_mouse_enter(Atlas.win, bat, 120, set_battery_icon);
    
    // Display widgets
    gtk_widget_show(bat);
}
