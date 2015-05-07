// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     vol.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/vol.h"
// 
// 
// PURPOSE:
// 
//     Creates a volume icon widget on the main status bar. Displays volume 
//     level and the icon changes color if music is playing.
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// FUNCTIONS:
// 
//     is_mute         - Check is mute is toggled
//     is_playing      - Check if music player is running
//     
//     get_volume      - Return current volume level
//     get_volume_icon - Return proper volume icon corresponding to volume level
//     
//     set_volume_icon - Set the volume widget icon
//     
//     display_volume  - Display the volume widget

// 
// 
// FILE STRUCTURE:
// 
//     * Includes and Declares
//     * Check Audio Settings
//     * Get Volume Attributes
//     * Set Volume Icon
//     * Display Volume Widget
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg Sep 15 2014 <> created
// 
//     gabeg Oct 04 2014 <> Added the header and included a function to check if
//                          mute is toggled.
// 
//     gabeg Nov 02 2014 <> Made it so that the volume widget did not have to 
//                          rely on the Atlas frame (being passed in as a parameter). 
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/vol.h"
#include "../hdr/atlas.h"
#include "../hdr/util.h"
#include <gtk/gtk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define   XPOS              75
#define   YPOS              0
#define   PIDOF          "pidof"
#define   MUSIC_PLAYER   "mocp"
#define   ICON_DIR       "/home/gabeg/.config/awesome/img/icons/vol/"
#define   ICON_EXT       ".png"


// Declares
static int is_mute();
static pid_t is_playing();
static int get_volume();
static void get_volume_icon(char *path);
static gboolean set_volume_icon(gpointer data);
void display_volume();



// ////////////////////////////////
// ///// CHECK AUDIO SETTINGS /////
// ////////////////////////////////

// Check if mute is toggled
static int is_mute() {
    
    // Get output from command
    char *cmd = "/home/gabeg/.config/dwm/src/atlas/scripts/vol -p -m";
    FILE *handle = popen(cmd, "r");
    char status[5];
    fgets(status, sizeof(status), handle);    
    fclose(handle);
    
    // Convert command output to boolean 
    if ( strcmp(status, "off\n") == 0 ) 
        return 1;
    else 
        return 0;
}



// Check if music player is running
static pid_t is_playing() {
    
    // Piece together command to check if music player is running
    size_t sz = strlen(PIDOF) + strlen(MUSIC_PLAYER) + 2;
    char cmd[sz];
    snprintf(cmd, sz, "%s %s", PIDOF, MUSIC_PLAYER);
    
    // Check if music player is running
    char line[3];
    FILE *proc = popen(cmd, "r");
    fgets(line, sizeof(line), proc);
    pclose(proc);
    
    // Return pid of music player process
    pid_t pid = strtoul(line, NULL, 10);
    
    return pid;
}



// /////////////////////////////////
// ///// GET VOLUME ATTRIBUTES /////
// /////////////////////////////////

// Return current volume level
static int get_volume() {
    
    // Get output from command
    char *cmd = "/home/gabeg/.config/dwm/src/atlas/scripts/vol -p -v";
    FILE *handle = popen(cmd, "r");
    char vol[5];
    fgets(vol, sizeof(vol), handle);    
    fclose(handle);
    
    // Convert command output to integer volume level
    int level = atoi(vol);
    
    return level;
}



// Return the proper volume icon
static void get_volume_icon(char *path) {
    
    // Initialize variables
    int level = get_volume();
    char *name;
    
    // Check if music is playing
    pid_t pid = is_playing();
    
    // Determine the correct volume icon
    if ( pid != 0 ) {
        if ( (level == 0) || (is_mute()) )
            name = "volMusMute";
        else if ( (level > 0) && (level <= 20) )
            name = "volMus0-20";
        else if ( (level > 20) && (level <= 40) )
            name = "volMus20-40";
        else if ( (level > 40) && (level <= 60) )
            name = "volMus40-60";
        else if ( (level > 60) && (level <= 80) )
            name = "volMus60-80";
        else if ( (level > 80) && (level <= 100) )
            name = "volMus80-100";
        else {
            fprintf(stderr, "%s '%d'\n", "ERROR: Could not match level", level);
            name = "volMusMute";
        }
    } else {
        if ( (level == 0) || (is_mute()) )
            name = "volMute";
        else if ( (level > 0) && (level <= 20) )
            name = "vol0-20";
        else if ( (level > 20) && (level <= 40) )
            name = "vol20-40";
        else if ( (level > 40) && (level <= 60) )
            name = "vol40-60";
        else if ( (level > 60) && (level <= 80) )
            name = "vol60-80";
        else if ( (level > 80) && (level <= 100) )
            name = "vol80-100";
        else {
            fprintf(stderr, "%s '%d'\n", "ERROR: Could not match level", level);
            name = "volMusMute";
        }
    }
    
    
    // Allocate memory for string
    size_t sz = strlen(ICON_DIR) + strlen(name) + strlen(ICON_EXT) + 1;
    snprintf(path, sz, "%s%s%s", ICON_DIR, name, ICON_EXT);
}



// ///////////////////////////
// ///// SET VOLUME ICON /////
// ///////////////////////////

// Set the volume widget icon
static gboolean set_volume_icon(gpointer data) {
    
    // Extract widget from pointer
    GtkWidget *widget = (GtkWidget *) data;
    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    
    // Get icon location
    char path[256];
    get_volume_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(children->data), path);
    
    // Free memory
    g_list_free(children);
    
    return TRUE;
} 



// /////////////////////////////////
// ///// DISPLAY VOLUME WIDGET /////
// /////////////////////////////////

// Display the volume widget
void display_volume() {
    
    // Initialize volume widget
    GtkWidget *win    = gtk_window_new(GTK_WINDOW_POPUP);
    GtkWidget *vol = gtk_image_new();
    
    // Set volume icon
    char path[256];
    get_volume_icon(path);
    gtk_image_set_from_file(GTK_IMAGE(vol), path);
    
    // Enable events on volume widget
    int pos[4] = {1366-XPOS, YPOS, 0, 20};
    setup_widget(win, NULL, pos);
    widget_mouse_enter(win, vol, 0, set_volume_icon);
    
    // Display widgets
    gtk_widget_show(vol);
    gtk_widget_show(win);
}
