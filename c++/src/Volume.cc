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
//     #include "Volume.h"
// 
// 
// PURPOSE:
// 
//     Creates a volume icon and attaches it to the status bar. Displays volume 
//     level and the icon changes color if music is playing.
// 
// 
// MODIFICATION HISTORY:
// 
//     gabeg May 02 2015 <> Created.
// 
//     gabeg May 07 2015 <> Finished converting the C implementation to C++.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Volume.h"
#include "../hdr/StatusItem.h"
#include "../hdr/StatusBar.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <iostream>
#include <string>

// Declares
static int is_mute();
static pid_t is_playing();

StatusItem<Gtk::Image> *Volume::widget;



// ////////////////////////////////
// ///// CHECK AUDIO SETTINGS /////
// ////////////////////////////////

// Check if mute is toggled
static int is_mute() {
    
    // Get output from command
    std::string cmd = "/home/gabeg/.config/dwm/src/atlas/scripts/vol -p -m";
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
std::string Volume::icon() {
    
    // Initialize variables
    std::string file = "/home/gabeg/.config/dwm/src/atlas/c++/config/Atlas.config";
    std::string cmd = Config::read(file, "volume_cmd");
    
    std::string name;
    std::string icon_dir = "/home/gabeg/.config/awesome/img/icons/vol/";
    std::string icon_ext = ".png";
    int level            = widget->percent(cmd);
    pid_t pid = is_playing();
    std::cout << "Volume: " << level << std::endl;
    std::cout << "Volume: " << pid << std::endl;
        
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
            std::cout << "Volume: Could not match level" << level << std::endl;
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
            std::cout << "Volume: Could not match level" << level << std::endl;
            name = "volMusMute";
        }
    }
    
    // Allocate memory for string
    std::string path = icon_dir + name+ icon_ext;
    std::cout << "Volume: " << path << std::endl;
    
    return path;
}



// /////////////////////////////////
// ///// DISPLAY VOLUME WIDGET /////
// /////////////////////////////////

// Display the volume widget
void Volume::display(Gtk::Box *bar) {
    std::string path = icon();
    
    widget = new StatusItem<Gtk::Image>(path);
    widget->attach(bar, StatusBar::ALIGN_RIGHT);
    widget->call(icon);
}
