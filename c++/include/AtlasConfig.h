/* *****************************************************************************
 * 
 * Name:    AtlasConfig.h
 * Class:   <AtlasConfig>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas configuration file utility.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_CONFIG_H
#define ATLAS_CONFIG_H

/* Includes */
#include <string>
#include <vector>

/* Namespaces */
namespace AtlasConfig
{
    std::string              fetch(std::string key);
    std::string              fetch(std::string section, std::string key);
    std::string              fetch(std::string file,    std::string section, std::string key);
    int                      fetch_int(std::string key);
    int                      fetch_int(std::string section, std::string key);
    int                      fetch_int(std::string file,    std::string section, std::string key);
    std::vector<std::string> parse(std::string file, std::string key, char delim);
    std::vector<std::string> parse(std::string str,  char        delim);
    std::string              cut(std::string str, int field, char delim);
    std::string              trim(std::string str);
    std::string              trim_lead(std::string str);
    std::string              trim_trail(std::string str);
    std::string              get_config_file(void);
    bool                     exists(std::string section);
};

#endif /* ATLAS_CONFIG_H */
