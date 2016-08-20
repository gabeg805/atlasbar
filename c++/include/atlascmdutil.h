/* *****************************************************************************
 * 
 * Name:    atlascmdutil.h
 * Class:   <atlas::cmd>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: An Atlas application utility for executing commands and parsing
 *              command output.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_CMD_UTIL_H
#define ATLAS_CMD_UTIL_H

/* Includes */
#include "atlas.h"
#include <string>

/* Namespaces */
namespace atlas
{
    /* Public functions */
    namespace cmd
    {
        std::string exec(std::string cmd);
        int         get_percent(std::string cmd);
    };
};

#endif /* ATLAS_CMD_UTIL_H */
