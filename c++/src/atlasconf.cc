/* *****************************************************************************
 * 
 * Name:    atlasconf.cc
 * Class:   <atlasconf>
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
#include "atlasconf.h"
#include "atlasio.h"
#include <libgen.h>
#include <string.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>

/* fetch -> find */

/* parse -> split. Change functionality so you have to do find first. Move to io */
/* Move is_white_space to io */
/* Move cut to io */
/* Move trim to io */
/* get_config_file -> get_file */
/* exists -> issection */
/* Search for is_config_section using terminal */

bool is_section(std::string section);

/* ************************************************************************** */
/* Return the default Atlas configuration file */
std::string atlasconf::get_file(void)
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
/* Read the specified file, in the given section, for value pair of key */
std::string atlasconf::find(std::string section, std::string key)
{
    if ( section.empty() )
        return "";
    if ( section.front() != '[' )
        section.insert(0, "[");
    if ( section.back() != ']' )
        section.append("]");

    static std::string file = atlasconf::get_file();
    std::ifstream      stream(file.c_str(), std::ifstream::in);
    std::string        delimiter = ":";
    std::string        line;
    std::string        setting;
    std::string        ret;
    size_t             loc;
    size_t             len;
    size_t             pos;
    bool               found = false;

    /* Find value pair of key */
    while ( std::getline(stream, line) ) {
        if ( atlasio::is_space(line) )
            continue;
        if ( is_section(line) ) {
            if ( section.compare(line) == 0 ) {
                found = true;
                continue;
            }
            else
                if ( found )
                    break;
        }
        if ( !found )
            continue;
        if ( key.empty() )
            return "Found";

        loc     = line.find(delimiter);
        setting = line.substr(0, loc);
        if ( setting.compare(key) != 0 )
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
/* Read value pairs in the given section and treat it as an integer */
int atlasconf::find_int(std::string section, std::string key)
{
    return atoi(atlasconf::find(section, key).c_str());
}

/* ************************************************************************** */
/* Determine if string is a section in the config file */
bool is_section(std::string section)
{
    uint8_t len = section.length();
    uint8_t i;

    if ( section[0] != '[' )
        return false;

    for ( i = 1; i < len; ++i ) {
        if ( section[i] == ']' )
            return true;
    }

    return false;
}
