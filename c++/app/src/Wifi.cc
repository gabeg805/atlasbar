/* *****************************************************************************
 * 
 * Name:    Wifi.cc
 * Class:   <Wifi>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas wifi strength indicator.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "Wifi.h"
#include "AtlasApp.h"
#include "AtlasAppSettings.h"
#include "AtlasConfig.h"
#include "AtlasCommand.h"
#include <gtkmm.h>
#include <iostream>
#include <string>

/* ***********************************
 * ***** CREATE WIFI APPLICATION *****
 * ***********************************
 */

void Wifi::create(void)
{
    Gtk::Image *image = new Gtk::Image(get_icon());
    set_margin(*image, 5, 0);
    init(image);
    connect_callback(update, 5);
}

/* *********************
 * ***** WIFI ICON *****
 * *********************
 */

bool Wifi::update(void *w)
{
    static_cast<Gtk::Image*>(w)->set(get_icon());
    return true;
}

std::string Wifi::get_icon(void)
{
    static std::string cmd   = AtlasConfig::fetch("wifi_cmd");
    static std::string dir   = AtlasConfig::fetch("wifi_icon_dir");
    static std::string ext   = ".png";
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::string name;

    // Determine correct icon name
    if ( level == 0 )
        name = "None";
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
        std::cout << "Wifi: Could not match level ~" << level << "~" << std::endl;
        name = "None";
    }

    return (dir + name + ext);
}
