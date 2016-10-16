/* *****************************************************************************
 * 
 * Name:    battery.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: A battery application for Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "battery.h"
#include "atlas.h"

/* Private functions */
static bool        setbatteryimage(void);
static std::string getbatteryimage(void);
static int         batteryclicked(void *event);

/* Globals */
static Gtk::Image *widget = NULL;

/* ************************************************************************** */
/* Create battery application */
AtlasApp & battery(void)
{
    widget = new Gtk::Image(getbatteryimage());
    atlas::app::set_margin(*widget, 5, 0);

    Gtk::EventBox *eventbox = new Gtk::EventBox();
    eventbox->add(*widget);
    eventbox->signal_button_release_event().connect(sigc::ptr_fun(batteryclicked));
    Glib::signal_timeout().connect_seconds(sigc::ptr_fun(setbatteryimage), 2);

    static AtlasApp app(eventbox, atlas::align::RIGHT);
    return app;
}

/* ************************************************************************** */
/* Set battery image */
bool setbatteryimage(void)
{
    std::string imgfile = getbatteryimage();
    if (access(imgfile.c_str(), F_OK) == 0)
        widget->set(imgfile);
    return true;
}

/* ************************************************************************** */
/* Return battery icon path */
std::string getbatteryimage(void)
{
    static std::string ext   = ".png";
    static std::string dir   = "/home/gabeg/scripts/programs/atlas/c++/img/bat/";
    static std::string cmd   = "/home/gabeg/scripts/programs/battery/bat -c";
    int                level = atlas::cmd::get_percent(cmd);
    return (dir+std::to_string(level)+ext);
}

/* ************************************************************************** */
/* Display notification bubble when clicked */
int batteryclicked(void *event)
{
    system("aria --body \"$(/home/gabeg/scripts/programs/battery/bat -c 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 1 &");
    return 0;
}
