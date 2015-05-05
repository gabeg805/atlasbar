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
#include "../hdr/vol.h"
#include "../hdr/util.h"

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>

// Declares
static int is_mute();
static pid_t is_playing();
static std::string get_volume_icon();

static GtkWidget *vol_event;


// ////////////////////////////////
// ///// CHECK AUDIO SETTINGS /////
// ////////////////////////////////

// Check if mute is toggled
static int is_mute() {
    
    // Get output from command
    std::string cmd = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/vol -p -m";
    FILE *handle    = popen(cmd.c_str(), "r");
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
    std::string pidof        = "pidof";
    std::string music_player = "mocp";
    std::string cmd          = pidof + " " +  music_player;
    printf("%s: %s\n", __FUNCTION__, cmd.c_str());
    // Check if music player is running
    char line[3];
    FILE *proc = popen(cmd.c_str(), "r");
    fgets(line, sizeof(line), proc);
    pclose(proc);
    
    // Return pid of music player process
    pid_t pid = strtoul(line, NULL, 10);
    
    return pid;
}



// /////////////////////////////////
// ///// GET VOLUME ATTRIBUTES /////
// /////////////////////////////////

// Return the proper volume icon
static std::string get_volume_icon() {
    
    // Initialize variables
    std::string icon_dir = "/home/gabeg/.config/awesome/img/icons/vol/";
    std::string icon_ext = ".png";
    std::string cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/vol -p -v";
    int level            = Atlas.get_percent(cmd);
    std::string name;
    
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
    std::string path = icon_dir + name+ icon_ext;
    return path;
}



// ///////////////////////////
// ///// SET VOLUME ICON /////
// ///////////////////////////

// Set the volume widget icon
gboolean set_volume_icon(gpointer data) {
    
    // Extract widget from pointer
    GList *children = gtk_container_get_children(GTK_CONTAINER(vol_event));
    
    // Get icon location
    std::string path = get_volume_icon();
    gtk_image_set_from_file(GTK_IMAGE(children->data), path.c_str());
    
    // Free memory
    g_list_free(children);
    
    return TRUE;
} 



// /////////////////////////////////
// ///// DISPLAY VOLUME WIDGET /////
// /////////////////////////////////

// Display the volume widget
void display_volume() {
    
    Statusbar::Image vol;
    vol.init(get_volume_icon);
    vol.setters(Atlas.bar, 1, 0);
    vol.set(0);
    
    // Initialize volume widget
    // GtkWidget *vol = gtk_image_new();
    
    // // Set volume icon
    // std::string path = get_volume_icon();
    // gtk_image_set_from_file(GTK_IMAGE(vol), path.c_str());
    
    // // Enable events on volume widget
    // vol_event = gtk_event_box_new();
    // widget_mouse_entera(vol_event, vol, 0, set_volume_icon);
    
    // // Display widgets
    // gtk_widget_show(vol);
}
