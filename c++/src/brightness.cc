/* *****************************************************************************
 * 
 * Name:    brightness.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: A brightness application for Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "brightness.h"
#include "atlas.h"

/* Private functions */
static void        signalbrightness(uint32_t key);
static bool        setbrightnessimage(void);
static std::string getbrightnessimage(void);
static int         brightnessclicked(void *event);

/* Globals */
static Gtk::Image *widget = NULL;

/* ************************************************************************** */
/* Create brightness application */
AtlasApp & brightness(void)
{
    widget = new Gtk::Image(getbrightnessimage());
    atlas::app::set_margin(*widget, 5, 0);

    Gtk::EventBox *eventbox = new Gtk::EventBox();
    eventbox->add(*widget);
    eventbox->signal_button_release_event().connect(sigc::ptr_fun(brightnessclicked));

    static AtlasApp app(eventbox, atlas::align::RIGHT);
    app.set_signal(signalbrightness, ATLAS_SIG_BRT);
    return app;
}

/* ************************************************************************** */
/* Signal callback to change brightness */
void signalbrightness(uint32_t key)
{
   if ( key == ATLAS_SIG_BRT_UP )
        system("xbacklight -inc 5 2> /dev/null");
    else if ( key == ATLAS_SIG_BRT_DOWN )
        system("xbacklight -dec 5 2> /dev/null");
    else
        ;
    setbrightnessimage();
}

/* ************************************************************************** */
/* Set brightness image */
bool setbrightnessimage(void)
{
    widget->set(getbrightnessimage());
    return true;
}

/* ************************************************************************** */
/* Return brightness icon path */
std::string getbrightnessimage(void)
{
    static std::string ext   = ".png";
    static std::string dir   = "/home/gabeg/scripts/programs/atlas/c++/img/bright/";
    static std::string cmd   = "/home/gabeg/scripts/programs/brightness/bright";
    int                level = atlas::cmd::get_percent(cmd);
    std::string        name;

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
    else
        name = "0-10";

    return (dir+name+ext);
}

/* ************************************************************************** */
/* Display notification bubble when clicked */
int brightnessclicked(void *event)
{
    system("aria --body \"$(bright 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 1 &");
    return 0;
}
