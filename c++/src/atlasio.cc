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
#include "AtlasConfig.h"
#include <time.h>
#include <fstream>
#include <iostream>
#include <string>

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
    static std::string file = AtlasConfig::fetch("main", "log");
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
