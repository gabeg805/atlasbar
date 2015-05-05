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
// FUNCTIONS:
// 
//     get_wifi      - Return current wifi level
//     get_wifi_icon - Return the proper wifi icon, given the current wifi level 
//     
//     set_wifi_icon - Set the wifi icon
//     
//     display_wifi  - Display the wifi widget
// 
// 
// FILE STRUCTURE:
// 
//     * Get Wifi Attributes
//     * Set Wifi Icon
//     * Display Wifi Widget
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
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/wifi.h"
#include "../hdr/atlas.h"
#include "../hdr/util.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define   XPOS              45
#define   YPOS              0
#define   ICON_DIR   "/home/gabeg/.config/awesome/img/icons/wifi/"
#define   ICON_EXT   ".png"


// Declares
static int get_wifi();
static void get_wifi_icon(char *path);
static gboolean set_wifi_icon(gpointer data);
void display_wifi();



// ///////////////////////////////
// ///// GET WIFI ATTRIBUTES /////
// ///////////////////////////////

// Return current wifi level
static int get_wifi() {
    
    // Get output from command
    char *cmd = "iw dev wlp1s0 link | grep signal | sed 's/^[ \\t]*//' | cut -f2 -d' '";
    FILE *handle = popen(cmd, "r");
    char temp[5];
    fgets(temp, sizeof(temp), handle);    
    fclose(handle);
    
    // Convert command output to an integer wifi level
    int level = atoi(temp);
    
    return level;
}



// Return the proper wifi icon
static void get_wifi_icon(char *path) {
    
    // Initialize variables
    int level = get_wifi();    
    char *name;
    
    // Determine the correct wifi icon
    if ( level == 0 )
        name = "wireNone";
    else if ( (level > -100) && (level <= -90) )
        name = "wire0-20";
    else if ( (level > -90) && (level <= -80) )
        name = "wire20-40";
    else if ( (level > -80) && (level <= -70) )
        name = "wire40-60";
    else if ( (level > -70) && (level <= -60) )
        name = "wire60-80";
    else if ( (level > -60) && (level <= -20) )
        name = "wire80-100";
    else {
        fprintf(stderr, "%s '%d'\n", "ERROR: Could not match level", level);
        name = "wireNone";
    }
    
    // Allocate memory for string
    size_t sz = strlen(ICON_DIR) + strlen(name) + strlen(ICON_EXT) + 1;
    snprintf(path, sz, "%s%s%s", ICON_DIR, name, ICON_EXT);
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
    char path[256];
    get_wifi_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(children->data), path);
    
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
    GtkWidget *win    = gtk_window_new(GTK_WINDOW_POPUP);
    GtkWidget *wifi = gtk_image_new();
    
    // Set widget icon
    char path[256];
    get_wifi_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(wifi), path);
    
    // Setup widget
    int pos[4] = {1366-XPOS, YPOS, 0, 20};
    setup_widget(win, NULL, pos);
    widget_mouse_enter(win, wifi, 5, set_wifi_icon);
    
    // Display widgets
    gtk_widget_show(wifi);
    gtk_widget_show(win);
}
