/* *****************************************************************************
 * 
 * Name:    atlasio.cc
 * Class:   None
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas input/output utility. Handles printing messages to
 *              stdout/stderr, as well as to a log file.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlasio.h"
#include "atlas.h"
#include "atlasconf.h"
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

/* ************************************************************************** */
/* Cut a string on a delimeter */
std::string atlasio::cut(std::string str, int field, char delim)
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

    return atlasio::trim(item);
}

/* ************************************************************************** */
/* Trim leading and trailing space */
std::string atlasio::trim(std::string str)
{
    str = atlasio::trim_lead(str);
    str = atlasio::trim_trail(str);
    return str;
}

/* ************************************************************************** */
/* Trim leading space */
std::string atlasio::trim_lead(std::string str)
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
std::string atlasio::trim_trail(std::string str)
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
/* Check if string is composed purely of white space */
bool atlasio::is_space(std::string str)
{
    return std::all_of(str.begin(), str.end(), isspace);
}

/* ************************************************************************** */
/* Split a string on the delimeter and put each piece into a vector */
std::vector<std::string> atlasio::split(std::string str, char delim)
{
    std::stringstream stream(str);
    std::vector<std::string> vec;
    std::string item;

    while ( std::getline(stream, item, delim) )
        vec.push_back(item);

    return vec;
}

/* ************************************************************************** */
std::string strtimenow(void)
{
    time_t     now     = time(0);
    struct tm *tstruct = localtime(&now);
    char       buf[128];
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", tstruct);
    std::string str(buf);
    return str;
}

/* ************************************************************************** */
/* Print message to stdout */
void atlasio::print(std::string str)
{
#ifdef ATLAS_DEBUG
    std::cout << atlas::prog << ": " << str << std::endl;
#endif
}

/* ************************************************************************** */
/* Print message to stderr */
void atlasio::printerr(std::string str)
{
#ifdef ATLAS_DEBUG
    std::cerr << atlas::prog << ": " << str << std::endl;
#endif
}

/* ************************************************************************** */
/* Print message to log */
void atlasio::lprint(std::string str)
{
    static std::string file = atlasconf::find("main", "log");
    std::ofstream      log;
    log.open(file, std::ios::app);
    log << "[" << strtimenow() << "] " << str << std::endl;
    log.close();
}

/* ************************************************************************** */
/* Print message to stdout and to the log */
void atlasio::debug(std::string str)
{
#ifdef ATLAS_DEBUG
    atlasio::print(str);
    atlasio::lprint(str);
#endif
}
