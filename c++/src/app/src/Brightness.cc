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

/* ************************************************************************** */
/* Create the application */
void Brightness::create(void)
{
    Gtk::Image *image = new Gtk::Image(get_icon());
    set_margin(*image, 5, 0);
    init(image, update);
}

/* ************************************************************************** */
/* Callback function to periodically update the application icon */
bool Brightness::update(void *w)
{
    static_cast<Gtk::Image*>(w)->set(get_icon());
    return true;
}

/* ************************************************************************** */
/* Return the path of the icon to be used */
std::string Brightness::get_icon(void)
{
    static std::string cmd   = AtlasConfig::fetch("brightness_cmd");
    static std::string dir   = AtlasConfig::fetch("brightness_icon_dir");
    static std::string ext   = ".png";
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::string name;

    if ( (level >= 0) && (level <= 10) )
        name = "0-10";
    else if ( (level > 10) && (level <= 20) )
        name = "10-20";
    else if ( (level > 20) && (level <= 30) )
        name = "20-30";
    else if ( (level > 30) && (level <= 40) )
        name = "30-40";
    else if ( (level > 40) && (level <= 50) )
        name = "40-50";
    else if ( (level > 50) && (level <= 60) )
        name = "50-60";
    else if ( (level > 60) && (level <= 70) )
        name = "60-70";
    else if ( (level > 70) && (level <= 80) )
        name = "70-80";
    else if ( (level > 80) && (level <= 90) )
        name = "80-90";
    else if ( (level > 90) && (level <= 100) )
        name = "90-100";
    else {
        std::cout << "Brightness: Could not match level ~" << level << "~" << std::endl;
        name = "0-10";
    }

    return (dir + name + ext);
}
