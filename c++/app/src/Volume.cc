/* *****************************************************************************
 * 
 * Name:    Volume.cc
 * Class:   <Volume>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas volume indicator application.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "Volume.h"
#include "AtlasApp.h"
#include "AtlasAppSettings.h"
#include "AtlasConfig.h"
#include "AtlasCommand.h"
#include <gtkmm.h>
#include <iostream>
#include <string>

/* Private functions */
static int is_mute(void);
static pid_t is_playing(void);

/* *************************************
 * ***** CREATE VOLUME APPLICATION *****
 * *************************************
 */

void Volume::create(void)
{
    Gtk::Image *image = new Gtk::Image(get_icon());
    set_margin(*image, 5, 0);
    init(image, update);
}

/* ***********************
 * ***** VOLUME ICON *****
 * ***********************
 */

bool Volume::update(void *w)
{
    static_cast<Gtk::Image*>(w)->set(get_icon());
    return true;
}

std::string Volume::get_icon(void)
{
    static std::string dir   = AtlasConfig::fetch("volume_icon_dir");
    static std::string cmd   = AtlasConfig::fetch("volume_cmd");
    static std::string ext   = ".png";
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::string name;
    std::string qualifier;

    if ( is_playing() ) 
        qualifier = "_music";

    if ( (level == 0) || is_mute() )
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
        std::cout << 
            "Volume " << 
            qualifier << ": Could not match level ~" << level << "~" << std::endl;
        name = "Mute";
    }

    return (dir + name + qualifier + ext);
}

/* ********************************
 * ***** CHECK AUDIO SETTINGS *****
 * ********************************
 */

/* Check if mute is toggled */
static int is_mute(void)
{
    static std::string cmd    = AtlasConfig::fetch("volume_mute_cmd");
    std::string        output = AtlasCommand::exec_cmd(cmd);
    return (output.compare("off\n") == 0);
}

/* Check if music player is running */
static pid_t is_playing(void)
{
    static std::string cmd    = AtlasConfig::fetch("volume_player_cmd");
    std::string        output = AtlasCommand::exec_cmd(cmd);
    return atol(output.c_str());
}
