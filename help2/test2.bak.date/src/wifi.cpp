// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     wifi.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/wifi.h"
// 
// 
// PURPOSE:
// 
//     Creates a wifi icon widget on the main status bar. Displays wifi
//     level as a series of bars showing the reception level.
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
//     gabeg Nov 02 2014 <> Made it so that the wifi widget did not have to rely on 
//                          the Atlas frame (being passed in as a parameter). 
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
#include "../hdr/wifi.h"
#include "../hdr/util.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include <string>

// Declares
static std::string get_wifi_icon();
static gboolean set_wifi_icon(gpointer data);



// ///////////////////////////////
// ///// GET WIFI ATTRIBUTES /////
// ///////////////////////////////

// Return the proper wifi icon
static std::string get_wifi_icon() {
    
    // Initialize variables
    std::string icon_dir = "/home/gabeg/.config/awesome/img/icons/wifi/";
    std::string icon_ext = ".png";
    std::string cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/wifi";
    int level            = Atlas.get_percent(cmd);
    std::string name;
    
    // Determine the correct wifi icon
    if ( level == 0 )
        name = "wireNone";
    else if ( (level > 0) && (level <= 20) )
        name = "wire0-20";
    else if ( (level > 20) && (level <= 40) )
        name = "wire20-40";
    else if ( (level > 40) && (level <= 60) )
        name = "wire40-60";
    else if ( (level > 60) && (level <= 80) )
        name = "wire60-80";
    else if ( (level > 80) && (level <= 100) )
        name = "wire80-100";
    else {
        fprintf(stderr, "%s '%d'\n", "ERROR: Could not match level", level);
        name = "wireNone";
    }
    
    // Allocate memory for string
    std::string path = icon_dir + name + icon_ext;
    return path;
}



// /////////////////////////
// ///// SET WIFI ICON /////
// /////////////////////////

// Update the wifi widget
static gboolean set_wifi_icon(gpointer data) {
    
    // Extract widget from pointer
    GtkWidget *widget = (GtkWidget *) data;
    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    
    // Get icon location
    std::string path = get_wifi_icon();
    gtk_image_set_from_file(GTK_IMAGE(children->data), path.c_str());
    
    // Free memory
    g_list_free(children);
    
    return TRUE;
} 



// ///////////////////////////////
// ///// DISPLAY WIFI WIDGET /////
// ///////////////////////////////

// Display the wifi widget
void display_wifi() {
    
    // Initialize widgets
    GtkWidget *wifi = gtk_image_new();
    
    // Set widget icon
    std::string path = get_wifi_icon();
    gtk_image_set_from_file(GTK_IMAGE(wifi), path.c_str());
    
    // Setup widget
    widget_mouse_enter(Atlas.win, wifi, 5, set_wifi_icon);
    
    // Display widgets
    gtk_widget_show(wifi);
}
