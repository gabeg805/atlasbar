/* *****************************************************************************
 * 
 * Name:    wifi.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: A wifi application for Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "wifi.h"
#include "atlas.h"

/* Private functions */
static bool        setwifiimage(void);
static std::string getwifiimage(void);
static int         wificlicked(void *event);

/* Globals */
static Gtk::Image *widget = NULL;

/* ************************************************************************** */
/* Create wifi application */
AtlasApp & wifi(void)
{
    widget = new Gtk::Image(getwifiimage());
    atlas::app::set_margin(*widget, 5, 0);

    Gtk::EventBox *eventbox = new Gtk::EventBox();
    eventbox->add(*widget);
    eventbox->signal_button_release_event().connect(sigc::ptr_fun(wificlicked));
    Glib::signal_timeout().connect_seconds(sigc::ptr_fun(setwifiimage), 1);

    static AtlasApp app(eventbox, atlas::align::RIGHT);
    return app;
}

/* ************************************************************************** */
/* Set wifi image */
bool setwifiimage(void)
{
    widget->set(getwifiimage());
    return true;
}

/* ************************************************************************** */
/* Return wifi icon path */
std::string getwifiimage(void)
{
    static std::string ext   = ".png";
    static std::string dir   = "/home/gabeg/scripts/programs/atlas/c++/img/wifi/";
    static std::string cmd   = "/home/gabeg/scripts/programs/wifi/wifi -s";
    int                level = atlas::cmd::get_percent(cmd);
    std::string        name;

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
    else
        name = "None";

    return (dir+name+ext);
}

/* ************************************************************************** */
/* Display notification bubble when clicked */
int wificlicked(void *event)
{
    system("aria --body \"$(wifi -s 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 1 &");
    return 0;
}
