#include "AtlasUserApp.h"
#include "AtlasApple.h"
#include "AtlasSignalType.h"
#include "AtlasConfig.h"
#include "AtlasCommand.h"
#include <gdkmm.h>
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>

#include <stdint.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <cstdlib>

/* ************************************************************************** */
std::string get_battery_icon(void)
{
    static std::string ext   = ".png";
    static std::string dir   = AtlasConfig::fetch("[battery]", "directory");
    static std::string cmd   = AtlasConfig::fetch("[battery]", "command");
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::stringstream ss;
    ss << level;

    std::cout << (dir + ss.str() + ext) << std::endl;

    return (dir + ss.str() + ext);
}

/* ************************************************************************** */
std::string get_wifi_icon(void)
{
    static std::string ext   = ".png";
    static std::string dir   = AtlasConfig::fetch("[wifi]", "directory");
    static std::string cmd   = AtlasConfig::fetch("[wifi]", "command");
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::string name;

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

    std::cout << (dir + name + ext) << std::endl;

    return (dir + name + ext);
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
std::string get_volume_icon(void)
{
    static std::string ext   = ".png";
    static std::string dir   = AtlasConfig::fetch("[volume]", "directory");
    static std::string cmd   = AtlasConfig::fetch("[volume]", "command");
    int                level = AtlasCommand::get_cmd_percent(cmd);
    std::string name;
    std::string qualifier;

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
        std::cout << 
            "Volume " << 
            qualifier << ": Could not match level ~" << level << "~" << std::endl;
        name = "Mute";
    }

    std::cout << (dir + name + qualifier + ext) << std::endl;

    return (dir + name + qualifier + ext);
}

/* ************************************************************************** */
std::string get_brightness_icon(void)
{
    static std::string ext   = ".png";
    static std::string dir   = AtlasConfig::fetch("[brightness]", "directory");
    static std::string cmd   = AtlasConfig::fetch("[brightness]", "command");
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

    std::cout << (dir + name + ext) << std::endl;

    return (dir + name + ext);
}

/* ************************************************************************** */
std::string get_date_text(void)
{
    std::string fmt  = AtlasConfig::fetch("[date]", "format");
    time_t      t    = time(NULL);
    struct tm*  now  = localtime(&t);
    static char str[30];

    strftime(str, sizeof(str), fmt.c_str(), now);

    return std::string(str);
}

/* ************************************************************************** */
int wifi_event(void *event)
{
    system("aria --body \"$(wifi -s 2>&1)\" --xpos 10 --ypos 20 --time 2 --delay 2 &");
    return 0;
}

/* ************************************************************************** */
int volume_signal(unsigned int key)
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
int brightness_signal(unsigned int key)
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
std::string get_workspace_text(void)
{
    std::string text = AtlasConfig::fetch("[workspace]", "text");
    return text;
}

/* ************************************************************************** */
int workspace_signal(unsigned int key)
{
    if ( (key & 0xf0) == AtlasSignal::SCREEN ) {
        unsigned int  val = (key & 0xf);
        FILE         *fp  = fopen("/home/gabeg/.config/dwm/stuffers.txt", "a+");
        fprintf(fp, "val 0x%0x\n", val);
        fclose(fp);
        std::cout << "key: 0x" << std::hex << key << " | val: " << val << std::endl;
        return val;
    }
    return -1;
}
