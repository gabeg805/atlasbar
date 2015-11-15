/* *****************************************************************************
 * 
 * Name:    AtlasConfig.cc
 * Class:   <AtlasConfig>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas application configuration file reader and parser.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasConfig.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

/* Declares */
std::string AtlasConfig::FILE = "/home/gabeg/scripts/programs/atlas/c++/src/common/atlas.config";

/* ************************************************************************** */
/* Read the config file for value pair of key */
std::string AtlasConfig::fetch(std::string key)
{
    return fetch(AtlasConfig::FILE, key);
}

/* ************************************************************************** */
/* Read the specified file for value pair of key */
std::string AtlasConfig::fetch(std::string file, std::string key)
{
    std::ifstream stream(file.c_str(), std::ifstream::in);
    std::string delimiter = ":";
    std::string line;
    std::string setting;
    std::string ret;
    size_t loc;
    size_t len;
    size_t pos;

    /* Find value pair of key */
    while ( std::getline(stream, line) ) {
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
/* Read value pairs from config file and treat it as an integer */
int AtlasConfig::fetch_int(std::string key)
{
    return atoi(fetch(AtlasConfig::FILE, key).c_str());
}

/* ************************************************************************** */
/* Read value pairs from the specified file and treat it as an integer */
int AtlasConfig::fetch_int(std::string file, std::string key)
{
    return atoi(fetch(file, key).c_str());
}

/* ************************************************************************** */
/* Parse the value pair on the delimeter and put each piece into a vector */
std::vector<std::string> AtlasConfig::parse(std::string file, std::string key, char delim)
{
    std::string str = fetch(file, key);
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
