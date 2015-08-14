/* *****************************************************************************
 * 
 * Name:    AtlasCommand.h
 * Class:   <AtlasCommand>
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
#ifndef ATLAS_COMMAND_H
#define ATLAS_COMMAND_H

/* Includes */
#include <string>

/* Namespaces */
namespace AtlasCommand
{
    std::string exec_cmd(std::string cmd);
    int         get_cmd_percent(std::string cmd);
};

#endif /* ATLAS_COMMAND_H */
