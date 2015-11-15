/* *****************************************************************************
 * 
 * Name:    AtlasConfig.h
 * Class:   <AtlasConfig>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas application config reader and parser.
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
    std::string              fetch(std::string file, std::string key);
    int                      fetch_int(std::string key);
    int                      fetch_int(std::string file, std::string key);
    std::vector<std::string> parse(std::string file, std::string key, char delim);
    std::vector<std::string> parse(std::string str, char delim);

    extern std::string FILE;
};

#endif /* ATLAS_CONFIG_H */
