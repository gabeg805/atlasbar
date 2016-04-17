/* *****************************************************************************
 * 
 * Name:    AtlasConfig.cc
 * Class:   <AtlasConfig>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas configuration file utility. Reads and parses a
 *              configuration file, be it the default file or a specified file.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasConfig.h"
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

bool is_white_space(std::string str);
bool is_config_section(std::string str);

/* ************************************************************************** */
/* Read the config file for value pair of key */
std::string AtlasConfig::fetch(std::string key)
{
    return AtlasConfig::fetch(AtlasConfig::get_config_file(), "", key);
}

/* ************************************************************************** */
/* Read the specified file for value pair of key */
std::string AtlasConfig::fetch(std::string section, std::string key)
{
    return AtlasConfig::fetch(AtlasConfig::get_config_file(), section, key);
}

/* ************************************************************************** */
/* Read the specified file, in the given section, for value pair of key */
std::string AtlasConfig::fetch(std::string file, std::string section, std::string key)
{
    if ( section.front() != '[' )
        section.insert(0, "[");
    if ( section.back() != ']' )
        section.append("]");

    std::ifstream stream(file.c_str(), std::ifstream::in);
    std::string   delimiter = ":";
    std::string   line;
    std::string   setting;
    std::string   ret;
    size_t        loc;
    size_t        len;
    size_t        pos;
    bool          found = false;

    /* Find value pair of key */
    while ( std::getline(stream, line) ) {
        if ( is_white_space(line) )
            continue;

        if ( is_config_section(line) ) {
            if ( (section.empty()) || (section.compare(line) == 0) )
                found = true;
            else
                if ( found )
                    break;
        }

        if ( !found )
            continue;

        loc     = line.find(delimiter);
        setting = line.substr(0, loc);

        if ( !key.empty() && setting.compare(key) != 0 )
            continue;

        /* Return value pair of key */
        len = line.length();
        ret = line.substr(loc+1, len);
        pos = ret.find_first_not_of(" \t");
        return ret.substr(pos, len);
    }

    return "";
}

/* ************************************************************************** */
/* Read value pairs from config file and treat it as an integer */
int AtlasConfig::fetch_int(std::string key)
{
    return atoi(AtlasConfig::fetch(AtlasConfig::get_config_file(), "", key).c_str());
}

/* ************************************************************************** */
/* Read value pairs in the given section and treat it as an integer */
int AtlasConfig::fetch_int(std::string section, std::string key)
{
    return atoi(AtlasConfig::fetch(AtlasConfig::get_config_file(), section, key).c_str());
}

/* ************************************************************************** */
/* Read value pairs from the specified file and treat it as an integer */
int AtlasConfig::fetch_int(std::string file, std::string section, std::string key)
{
    return atoi(AtlasConfig::fetch(file, section, key).c_str());
}

/* ************************************************************************** */
/* Parse the value pair on the delimeter and put each piece into a vector */
std::vector<std::string> AtlasConfig::parse(std::string file, std::string key, char delim)
{
    std::string str = AtlasConfig::fetch(file, key);
    return parse(str, delim);
}

/* ************************************************************************** */
/* Parse a string on the delimeter and put each piece into a vector */
std::vector<std::string> AtlasConfig::parse(std::string str, char delim)
{
    std::stringstream stream(str);
    std::vector<std::string> vec;
    std::string item;

    while ( std::getline(stream, item, delim) )
        vec.push_back(item);

    return vec;
}

/* ************************************************************************** */
/* Return the default Atlas configuration file */
std::string AtlasConfig::get_config_file(void)
{
    static std::string configfile;
    static bool        pass = false;

    if ( !pass ) {
        std::string   cmdfile = "/proc/"+std::to_string(getpid())+"/cmdline";
        std::ifstream stream(cmdfile.c_str(), std::ifstream::in);
        std::string   line;
        std::getline(stream, line);

        char buf[128];
        memset(buf, 0, sizeof(buf));
        getcwd(buf, sizeof(buf));

        std::string cmd;
        if ( line[0] == '/' )
            cmd = line;
        else {
            std::string cwd(buf);
            cmd = cwd+"/"+line;
        }
        std::string parent = dirname((char*)cmd.c_str());

        configfile = parent+"/conf/atlas.conf";
        pass       = true;
    }

    return configfile;
}

/* ************************************************************************** */
/* Cut a string on a delimeter */
std::string AtlasConfig::cut(std::string str, int field, char delim)
{
    std::stringstream stream(str);
    std::string       item;
    uint8_t           count = 1;

    while ( std::getline(stream, item, delim) ) {
        if ( count == field )
            break;
        item = "";
        ++count;
    }

    return AtlasConfig::trim(item);
}

/* ************************************************************************** */
/* Trim leading and trailing space */
std::string AtlasConfig::trim(std::string str)
{
    str = AtlasConfig::trim_lead(str);
    str = AtlasConfig::trim_trail(str);
    return str;
}

/* ************************************************************************** */
/* Trim leading space */
std::string AtlasConfig::trim_lead(std::string str)
{
    uint8_t len = str.length();
    uint8_t i;
    for ( i = 0; i < len; ++i ) {
        if ( isspace(str[i]) ) {
            str.erase(i, 1);
            --i;
        }
        else
            break;
    }

    return str;
}

/* ************************************************************************** */
/* Trim trailing space */
std::string AtlasConfig::trim_trail(std::string str)
{
    uint8_t len = str.length();
    uint8_t i;
    for ( i = len-1; i >= 0; --i ) {
        if ( isspace(str[i]) )
            str.erase(i, 1);
        else
            break;
    }

    return str;
}

/* ************************************************************************** */
/* Check if config section exists */
bool AtlasConfig::exists(std::string section)
{
    std::string str = AtlasConfig::fetch(section, "");
    return !str.empty();
}

/* ************************************************************************** */
/* Check if string is composed purely of white space */
bool is_white_space(std::string str)
{
    return std::all_of(str.begin(), str.end(), isspace);
}

/* ************************************************************************** */
/* Check if string is a section in the configuration file */
bool is_config_section(std::string str)
{
    uint8_t len = str.length();
    uint8_t i;

    if ( str[0] != '[' )
        return false;

    for ( i = 1; i < len; ++i ) {
        if ( str[i] == ']' )
            return true;
    }

    return false;
}
