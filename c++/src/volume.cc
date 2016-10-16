/* *****************************************************************************
 * 
 * Name:    volume.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: A volume application for Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "volume.h"
#include "atlas.h"

/* Private functions */
static void        signalvolume(uint32_t key);
static bool        setvolumeimage(void);
static std::string getvolumeimage(void);
static int         volumeclicked(void *event);

/* Globals */
static Gtk::Image *widget = NULL;

/* ************************************************************************** */
/* Create volume application */
AtlasApp & volume(void)
{
    widget = new Gtk::Image(getvolumeimage());
    atlas::app::set_margin(*widget, 5, 0);

    Gtk::EventBox *eventbox = new Gtk::EventBox();
    eventbox->add(*widget);
    eventbox->signal_button_release_event().connect(sigc::ptr_fun(volumeclicked));

    static AtlasApp app(eventbox, atlas::align::RIGHT);
    app.set_signal(signalvolume, ATLAS_SIG_VOL);
    return app;
}

/* ************************************************************************** */
/* Signal callback to change volume */
void signalvolume(uint32_t key)
{
    if ( key == ATLAS_SIG_VOL_PLAY )
        system("mocp -G");
    else if ( key == ATLAS_SIG_VOL_NEXT )
        system("mocp -f");
    else if ( key == ATLAS_SIG_VOL_PREV )
        system("mocp -r");
    else if ( key == ATLAS_SIG_VOL_UP )
        system("amixer -q set Master 5%+");
    else if ( key == ATLAS_SIG_VOL_DOWN )
        system("amixer -q set Master 5%-");
    else if ( key == ATLAS_SIG_VOL_MUTE )
        system("amixer -q set Master toggle");
    else
        ;
    setvolumeimage();
}

/* ************************************************************************** */
/* Set volume image */
bool setvolumeimage(void)
{
    std::string imgfile = getvolumeimage();
    if (access(imgfile.c_str(), F_OK) == 0)
        widget->set(imgfile);
    return true;
}

/* ************************************************************************** */
/* Return volume string of volume icon path */
std::string getvolumeimage(void)
{
    static std::string ext   = ".png";
    static std::string dir   = "/home/gabeg/scripts/programs/atlas/c++/img/vol/";
    static std::string cmd   = "/home/gabeg/scripts/programs/volume/vol -p -v";
    int                level = atlas::cmd::get_percent(cmd);
    std::string        name;
    std::string        qualifier;

    static std::string pidcmd    = "/usr/bin/pidof mocp";
    std::string        pidoutput = atlas::cmd::exec(pidcmd);
    if ( atol(pidoutput.c_str()) ) 
        qualifier = "_music";

    static std::string mutecmd    = "/home/gabeg/scripts/programs/volume/vol -p -m";
    std::string        muteoutput = atlas::cmd::exec(mutecmd);
    if ( (level == 0) || (muteoutput.compare("off\n") == 0) )
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
    else
        name = "Mute";

    return (dir+name+qualifier+ext);
}

/* ************************************************************************** */
/* Display notification bubble when clicked */
int volumeclicked(void *event)
{
    system("aria --body \"$(vol 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 1 &");
    return 0;
}
