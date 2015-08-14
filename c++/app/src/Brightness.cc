/* *****************************************************************************
 * 
 * Name:    Brightness.cc
 * Class:   <Brightness>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas screen brightness indicator application.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "Brightness.h"
#include "AtlasApp.h"
#include "AtlasAppSettings.h"
#include "AtlasCommand.h"
#include "AtlasConfig.h"
#include <gtkmm.h>
#include <iostream>
#include <string>

/* *****************************************
 * ***** CREATE BRIGHTNESS APPLICATION *****
 * *****************************************
 */

void Brightness::create(void)
{
    Gtk::Image *image = new Gtk::Image(get_icon());
    set_margin(*image, 5, 0);
    init(image, update);
}

/* ***************************
 * ***** BRIGHTNESS ICON *****
 * ***************************
 */

bool Brightness::update(void *w)
{
    static_cast<Gtk::Image*>(w)->set(get_icon());
    return true;
}

std::string Brightness::get_icon(void)
{
    static std::string cmd   = AtlasConfig::fetch("brightness_cmd");
    static std::string dir   = AtlasConfig::fetch("brightness_icon_dir");
    static std::string ext   = ".png";
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::string name;

    if ( (level >= 0) && (level <= 15) )
        name = "0-15";
    else if ( (level > 15) && (level <= 30) )
        name = "15-30";
    else if ( (level > 30) && (level <= 45) )
        name = "30-45";
    else if ( (level > 45) && (level <= 60) )
        name = "45-60";
    else if ( (level > 60) && (level <= 75) )
        name = "60-75";
    else if ( (level > 75) && (level <= 100) )
        name = "75-100";
    else {
        std::cout << "Brightness: Could not match level ~" << level << "~" << std::endl;
        name = "75-100";
    }

    return (dir + name + ext);
}
