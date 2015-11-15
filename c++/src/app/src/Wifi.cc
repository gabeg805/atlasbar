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
#include <gdkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>

/* ************************************************************************** */
/* Display the Aria notification bubble on an event */
static bool do_stuff_please(GdkEventCrossing *event)
{
    system("aria --body \"$(wifi -s)\" --xpos 10 --ypos 20 --time 2 --delay 2 &");
    return true;
}

/* ************************************************************************** */
/* Create the application */
void Wifi::create(void)
{
    Gtk::Image *image = new Gtk::Image(get_icon());
    Gtk::EventBox *event = new Gtk::EventBox();
    set_margin(*image, 5, 0);
    event->add(*image);
    event->signal_enter_notify_event().connect(sigc::ptr_fun(&do_stuff_please));
    init(event);
    connect_callback(update, 5);
}

/* ************************************************************************** */
/* Callback function to periodically update the application icon */
bool Wifi::update(void *w)
{
    Gtk::Widget *widget = static_cast<Gtk::EventBox*>(w)->get_child();
    static_cast<Gtk::Image*>(widget)->set(get_icon());
    return true;
}

/* ************************************************************************** */
/* Return the path of the icon to be used */
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
