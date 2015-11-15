/* *****************************************************************************
 * 
 * Name:    Battery.cc
 * Class:   <Battery>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas battery indicator application. 
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "Battery.h"
#include "AtlasApp.h"
#include "AtlasAppSettings.h"
#include "AtlasCommand.h"
#include "AtlasConfig.h"
#include <gtkmm.h>
#include <sstream>
#include <string>

/* ************************************************************************** */
/* Create the application */
void Battery::create(void)
{
    Gtk::Image *image = new Gtk::Image(get_icon());
    set_margin(*image, 5, 0);
    init(image);
    connect_callback(update, 2);
}

/* ************************************************************************** */
/* Callback function to periodically update the application icon */
bool Battery::update(void *w)
{
    static_cast<Gtk::Image*>(w)->set(get_icon());
    return true;
}

/* ************************************************************************** */
/* Return the path of the icon to be used */
std::string Battery::get_icon(void)
{
    static std::string dir   = AtlasConfig::fetch("battery_icon_dir");
    static std::string cmd   = AtlasConfig::fetch("battery_cmd");
    static std::string ext   = ".png";
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::stringstream ss;
    ss << level;

    return (dir + ss.str() + ext);
}
