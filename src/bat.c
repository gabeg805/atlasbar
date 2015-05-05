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
// FUNCTIONS:
// 
//     get_charge       - Return current battery level
//     get_battery_icon - Return the proper battery icon, given the current 
//                        battery level
//     
//     set_battery_icon - Set the battery icon
//     
//     display_battery  - Display the battery widget
// 
// 
// FILE STRUCTURE:
// 
//     * Get Battery Attributes
//     * Set Battery Icon
//     * Display Battery Widget
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
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/bat.h"
#include "../hdr/atlas.h"
#include "../hdr/util.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define   XPOS              20
#define   YPOS              0
#define   CHARGE_NOW_FILE      "/sys/class/power_supply/BAT0/charge_now"
#define   CHARGE_FULL_FILE     "/sys/class/power_supply/BAT0/charge_full"
#define   CHARGE_STATUS_FILE   "/sys/class/power_supply/BAT0/status"
#define   ICON_DIR             "/home/gabeg/.config/awesome/img/icons/bat/bat"
#define   ICON_SUF             "-charge"
#define   ICON_EXT             ".png"

// Declares
static int get_charge();
static void get_battery_icon(char *path);
static gboolean set_battery_icon(gpointer data);
void display_battery();



// //////////////////////////////////
// ///// GET BATTERY ATTRIBUTES /////
// //////////////////////////////////

// Return the battery charge level
static int get_charge() {
    
    // Initialize file handler
    FILE *handle;
    
    // Get contents of NOW file
    handle = fopen(CHARGE_NOW_FILE, "r");
    char charge_now[10];
    fgets(charge_now, sizeof(charge_now), handle);    
    fclose(handle);
    
    // Get contents of FULL file
    handle = fopen(CHARGE_FULL_FILE, "r");
    char charge_full[10];
    fgets(charge_full, sizeof(charge_full), handle);    
    fclose(handle);
    
    // Get contents of STATUS file
    handle = fopen(CHARGE_STATUS_FILE, "r");
    char charge_status[10];
    fgets(charge_status, sizeof(charge_status), handle);    
    fclose(handle);
    
    // Calculate charge
    int charge;
    if ( strcmp(charge_status, "Charging\n") == 0 ) 
        charge = -1;
    else {
        int now = atoi(charge_now);
        int full = atoi(charge_full);
        charge = 100.0f * now / full;
    }
    
    return charge;
}    



// Return the proper battery icon
static void get_battery_icon(char *path) {
    
    // Initialize variables
    int charge = get_charge();    
    
    // Determine the correct volume icon
    size_t sz  = 0;
    size_t sza = strlen(ICON_DIR) + strlen(ICON_SUF) + strlen(ICON_EXT) + 1;
    size_t szb = strlen(ICON_DIR) + sizeof(charge) + strlen(ICON_EXT) + 1;
    
    if ( charge == -1 ) 
        sz = sza;
    else 
        sz = szb;
    
    // Allocate memory for string
    if ( sz == sza )
        snprintf(path, sz, "%s%s%s", ICON_DIR, ICON_SUF, ICON_EXT);
    else
        snprintf(path, sz, "%s%d%s", ICON_DIR, charge, ICON_EXT);
}



// ////////////////////////////
// ///// SET BATTERY ICON /////
// ////////////////////////////

// Set the battery icon on the widget
static gboolean set_battery_icon(gpointer data) {
    
    // Get battery icon
    char path[256];
    get_battery_icon(path);
    GdkPixbuf * ploob = gdk_pixbuf_new_from_file(path, NULL);
    
    // Set icon onto widget
    GtkWidget *widget = (GtkWidget *) data;
    GList * children = gtk_container_get_children (GTK_CONTAINER (widget));
    gtk_image_set_from_pixbuf(GTK_IMAGE(children->data), ploob);
    
    // Free memory
    g_list_free (children);
    
    return TRUE;
} 



// //////////////////////////////////
// ///// DISPLAY BATTERY WIDGET /////
// //////////////////////////////////

// Display the battery widget
void display_battery() {
    
    // Initialize widgets
    GtkWidget *win = gtk_window_new(GTK_WINDOW_POPUP);
    GtkWidget *bat = gtk_image_new();
    
    // Set widget icon
    char path[256];
    get_battery_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(bat), path);
    
    // Setup widget
    int pos[4] = {1366-XPOS, YPOS, 0, 20};
    setup_widget(win, NULL, pos);
    widget_mouse_enter(win, bat, 120, set_battery_icon);
    
    // Display widgets
    gtk_widget_show(bat);
    gtk_widget_show(win);
}
