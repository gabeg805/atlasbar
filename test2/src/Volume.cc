// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     Volume.cc
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/Volume.h"
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
#include "../hdr/BarImage.h"
#include "../hdr/StatusBar.h"
#include "../hdr/Volume.h"
#include "../hdr/util.h"

#include <gtkmm.h>
#include <iostream>
#include <string>

// Declares
static int is_mute();
static pid_t is_playing();

using namespace std;

BarImage *Volume::widget;



// ////////////////////////////////
// ///// CHECK AUDIO SETTINGS /////
// ////////////////////////////////

// Check if mute is toggled
static int is_mute() {
    
    // Get output from command
    string cmd = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/vol -p -m";
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
    string pidof        = "pidof";
    string music_player = "mocp";
    string cmd          = pidof + " " +  music_player;
    
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

void Volume::set() {
    widget->set(icon);
}

// Return the proper volume icon
string Volume::icon() {
    
    // Initialize variables
    string icon_dir = "/home/gabeg/.config/awesome/img/icons/vol/";
    string icon_ext = ".png";
    string cmd      = "/home/gabeg/.config/dwm/src/atlas/test/src/scripts/vol -p -v";
    int level       = get_percent(cmd);
    string name;
    
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
            cout << "ERROR: Could not match level" << level << endl;
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
            cout << "ERROR: Could not match level" << level << endl;
            name = "volMusMute";
        }
    }
    
    // Allocate memory for string
    string path = icon_dir + name+ icon_ext;
    
    return path;
}



// /////////////////////////////////
// ///// DISPLAY VOLUME WIDGET /////
// /////////////////////////////////

// Display the volume widget
void Volume::display(Gtk::Box *bar) {
    string path = icon();
    widget = new BarImage(bar, path);
    widget->position(StatusBar::RIGHT);
}
