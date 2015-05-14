// **********************************************************************************
// 
// Name:    Volume.cc
// Class:   <Volume>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: Creates a volume icon and attaches it to the status bar. Displays volume 
//              level and the icon changes color if music is playing.
//              
// Notes: None.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/Volume.h"
#include "../hdr/StatusSimple.h"
#include "../hdr/Config.h"

#include <gtkmm.h>
#include <iostream>
#include <string>

// Declares
static int is_mute();
static pid_t is_playing();

StatusSimple Volume::widget;



// ////////////////////////////////
// ///// CHECK AUDIO SETTINGS /////
// ////////////////////////////////

// Check if mute is toggled
static int is_mute() {
    std::string cmd    = Config::fetch("volume_mute_cmd");
    std::string output = StatusWidget::command(cmd);
    
    if ( output.compare("off\n") == 0 ) {
        return 1;
    } else 
        return 0;
}



// Check if music player is running
static pid_t is_playing() {
    std::string cmd    = Config::fetch("volume_player_cmd");
    std::string output = StatusWidget::command(cmd);
    
    return atol( output.c_str() );
}



// /////////////////////////////////
// ///// GET VOLUME ATTRIBUTES /////
// /////////////////////////////////

// Return the proper volume icon
std::string Volume::icon() {
    
    // Icon path variables
    std::string name;
    std::string qualifier = "";
    std::string dir       = Config::fetch(Config::FILE, "volume_icon_dir");
    std::string cmd       = Config::fetch(Config::FILE, "volume_cmd");
    int level             = StatusWidget::percent(cmd);
    
    // Determine correct icon name
    if ( is_playing() != 0 ) 
        qualifier = "_music";
    
    if ( (level == 0) || (is_mute()) )
        name = "Mute";
    else if ( (level > 0) && (level <= 20) )
        name = "0-20";
    else if ( (level > 20) && (level <= 40) )
        name = "20-40";
    else if ( (level > 40) && (level <= 60) )
        name = "40-60";
    else if ( (level > 60) && (level <= 80) )
        name = "60-80";
    else if ( (level > 80) && (level <= 100) )
        name = "80-100";
    else {
        std::cout << "Volume " << qualifier << ": Could not match level" << level << std::endl;
        name = "Mute";
    }
    
    return (dir + name + qualifier + ".png");
}



// /////////////////////////////////
// ///// DISPLAY VOLUME WIDGET /////
// /////////////////////////////////

// Display the volume widget
void Volume::create() {
    // widget = new StatusSimple();
    widget.init    <Gtk::Image> (icon());
    widget.padding <Gtk::Image> (5, 0);
    widget.call(icon);
}
