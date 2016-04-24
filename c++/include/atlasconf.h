/* *****************************************************************************
 * 
 * Name:    atlasconf.h
 * Class:   <atlasconf>
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

/* Namespace */
namespace atlasconf
{
    std::string get_file(void);
    std::string find(std::string section, std::string key);
    int         find_int(std::string section, std::string key);
};

#endif /* ATLAS_CONFIG_H */
