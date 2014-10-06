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
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/vol.h"
#include "../hdr/util.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define   PIDOF          "pidof"
#define   MUSIC_PLAYER   "mocp"
#define   ICON_DIR       "/home/gabeg/.config/awesome/img/icons/vol/"
#define   ICON_EXT       ".png"


// Declares
int is_mute();
pid_t is_playing();
int get_volume();
char * get_volume_icon();
gboolean set_volume_icon(gpointer data);
void display_volume(GtkWidget *bar);



// ////////////////////////////////
// ///// CHECK AUDIO SETTINGS /////
// ////////////////////////////////

// Check if mute is toggled
int is_mute() {
    
    // Get output from command
    char *cmd = "amixer get Master | tail -1 | awk '{print $6}' | sed -e 's/\\[//; s/\\]//; s/\\%//'";
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
pid_t is_playing() {
    
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
int get_volume() {
    
    // Get output from command
    char *cmd = "amixer get Master | tail -1 | awk '{print $4}' | sed -e 's/\\[//; s/\\]//; s/\\%//'";
    FILE *handle = popen(cmd, "r");
    char temp[5];
    fgets(temp, sizeof(temp), handle);    
    fclose(handle);
    
    // Convert command output to integer volume level
    int level = atoi(temp);
    
    return level;
}



// Return the proper volume icon
char * get_volume_icon() {
    
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
    char *output = malloc(sz);
    snprintf(output, sz, "%s%s%s", ICON_DIR, name, ICON_EXT);
    
    return output;
}



// ///////////////////////////
// ///// SET VOLUME ICON /////
// ///////////////////////////

// Set the volume widget icon
gboolean set_volume_icon(gpointer data) {
    
    // Extract widget from pointer
    GtkWidget *widget = (GtkWidget *) data;
    GList *children = gtk_container_get_children(GTK_CONTAINER(widget));
    
    // Get icon location
    char *vol_icon = get_volume_icon();
    gtk_image_set_from_file(GTK_IMAGE(children->data), vol_icon);
    
    // Free memory
    free(vol_icon);
    g_list_free(children);
    
    return TRUE;
} 



// /////////////////////////////////
// ///// DISPLAY VOLUME WIDGET /////
// /////////////////////////////////

// Display the volume widget
void display_volume(GtkWidget *bar) {
    
    // Initialize volume widget
    GtkWidget *vol = gtk_image_new();
    
    // Set volume icon
    char *vol_icon = get_volume_icon();
    gtk_image_set_from_file(GTK_IMAGE(vol), vol_icon);
    
    // Enable events on volume widget
    widget_event(bar, vol, 0, set_volume_icon);
}
