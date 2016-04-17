/* *****************************************************************************
 * 
 * Name:    StatusBar.h
 * Class:   <StatusBar>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Status Bar container.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasUser.h"
#include "AtlasUserApp.h"
#include "AtlasUserAppBuilder.h"
#include "AtlasCommand.h"
#include "AtlasConfig.h"
#include "AtlasSignalType.h"
#include "atlasio.h"
#include <stdint.h>
#include <cstdlib>
#include <ctime>
#include <gdkmm.h>
#include <iostream>
#include <string>
#include <vector>

/* ************************************************************************** */
/* Return the user defined status bar applications */
AtlasUserApp* create_user_apps(void)
{
    static AtlasUserAppBuilder *builder = new AtlasUserAppBuilder(6);
    builder->new_app("battery",    {get_battery_icon,    battery_event,    NULL});
    builder->new_app("wifi",       {get_wifi_icon,       wifi_event,       NULL});
    builder->new_app("volume",     {get_volume_icon,     volume_event,     volume_signal});
    builder->new_app("brightness", {get_brightness_icon, brightness_event, brightness_signal});
    builder->new_app("date",       {get_date_text,       NULL,             NULL});
    builder->new_app("workspace",  {get_workspace_text,  NULL,             workspace_signal});
    return builder->get_apps();
}

/* ************************************************************************** */
/* Return the battery icon string */
std::string get_battery_icon(void)
{
    static std::string ext   = ".png";
    static std::string dir   = AtlasConfig::fetch("[battery]", "directory");
    static std::string cmd   = AtlasConfig::fetch("[battery]", "command");
    int                level = AtlasCommand::get_cmd_percent(cmd);
    return (dir+std::to_string(level)+ext);
}

/* ************************************************************************** */
/* Return the wifi icon string */
std::string get_wifi_icon(void)
{
    static std::string ext   = ".png";
    static std::string dir   = AtlasConfig::fetch("[wifi]", "directory");
    static std::string cmd   = AtlasConfig::fetch("[wifi]", "command");
    int                level = AtlasCommand::get_cmd_percent(cmd);
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
    else {
        atlasio::debug("Unkown wifi strength '"+std::to_string(level)+"'.");
        name = "None";
    }
    return (dir+name+ext);
}

/* ************************************************************************** */
/* Check if mute is toggled */
static int volume_is_mute(void)
{
    static std::string cmd    = AtlasConfig::fetch("[volume]", "mute");
    std::string        output = AtlasCommand::exec_cmd(cmd);
    return (output.compare("off\n") == 0);
}

/* ************************************************************************** */
/* Check if music player is running */
static pid_t volume_is_playing(void)
{
    static std::string cmd    = AtlasConfig::fetch("[volume]", "player");
    std::string        output = AtlasCommand::exec_cmd(cmd);
    return atol(output.c_str());
}

/* ************************************************************************** */
/* Return the volume icon string */
std::string get_volume_icon(void)
{
    static std::string ext   = ".png";
    static std::string dir   = AtlasConfig::fetch("[volume]", "directory");
    static std::string cmd   = AtlasConfig::fetch("[volume]", "command");
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::string        name;
    std::string        qualifier;

    if ( volume_is_playing() ) 
        qualifier = "_music";

    if ( (level == 0) || volume_is_mute() )
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
        atlasio::debug("Unkown volume level '"+std::to_string(level)+"'.");
        name = "Mute";
    }

    return (dir+name+qualifier+ext);
}

/* ************************************************************************** */
/* Return the brightness icon string */
std::string get_brightness_icon(void)
{
    static std::string ext   = ".png";
    static std::string dir   = AtlasConfig::fetch("[brightness]", "directory");
    static std::string cmd   = AtlasConfig::fetch("[brightness]", "command");
    int                level = AtlasCommand::get_cmd_percent(cmd);
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
    else {
        atlasio::debug("Unkown brightness level '"+std::to_string(level)+"'.");
        name = "0-10";
    }

    return (dir+name+ext);
}

/* ************************************************************************** */
/* Return the date text string */
std::string get_date_text(void)
{
    std::string fmt  = AtlasConfig::fetch("date", "format");
    time_t      t    = time(NULL);
    struct tm*  now  = localtime(&t);
    static char str[30];

    strftime(str, sizeof(str), fmt.c_str(), now);
    return std::string(str);
}

/* ************************************************************************** */
/* Execute the battery event */
int battery_event(void *event)
{
    system("aria --body \"$(/home/gabeg/scripts/programs/battery/bat -c 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 1 &");
    return 0;
}

/* ************************************************************************** */
/* Execute the wifi event */
int wifi_event(void *event)
{
    system("aria --body \"$(wifi -s 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 1 &");
    return 0;
}

/* ************************************************************************** */
/* Execute the volume event */
int volume_event(void *event)
{
    system("aria --body \"$(vol 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 1 &");
    return 0;
}

/* ************************************************************************** */
/* Execute the brightness event */
int brightness_event(void *event)
{
    system("aria --body \"$(bright 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 1 &");
    return 0;
}

/* ************************************************************************** */
/* Execute the volume signal */
int volume_signal(uint8_t key)
{
    switch ( key ) {
    case AtlasSignal::TRACK_PLAY:
        system("mocp -G");
        break;
    case AtlasSignal::TRACK_NEXT:
        system("mocp -f");
        break;
    case AtlasSignal::TRACK_PREV:
        system("mocp -r");
        break;
    case AtlasSignal::VOL_UP:
        system("amixer -q set Master 5%+");
        break;
    case AtlasSignal::VOL_DOWN:
        system("amixer -q set Master 5%-");
        break;
    case AtlasSignal::VOL_MUTE:
        system("amixer -q set Master toggle");
        break;
    default:
        return -1;
    }

    return 0;
}

/* ************************************************************************** */
/* Execute the brightness signal */
int brightness_signal(uint8_t key)
{
    switch ( key ) {
    case AtlasSignal::BRIGHT_UP:
        system("xbacklight -inc 10");
        break;
    case AtlasSignal::BRIGHT_DOWN:
        system("xbacklight -dec 10");
        break;
    default:
        return -1;
    }

    return 0;
}

/* ************************************************************************** */
/* Return the workspace text string */
std::string get_workspace_text(void)
{
    std::string text = AtlasConfig::fetch("workspace", "text");
    return text;
}

/* ************************************************************************** */
/* Execute the workspace signal */
int workspace_signal(uint8_t key)
{
    if ( (key & 0xf0) == AtlasSignal::SCREEN )
        return (key & 0xf);
    else
        return -1;
}