/* *****************************************************************************
 * 
 * Name:    AtlasCommand.cc
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

/* Includes */
#include "AtlasCommand.h"
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <string>

/* ************************
 * ***** COMMAND EXEC *****
 * ************************
 */

/* Return program command output */
std::string AtlasCommand::exec_cmd(std::string cmd)
{
    FILE       *stream = popen(cmd.c_str(), "r");
    std::string output;
    static char buf[256];

    if ( stream == NULL )
        return "Fail.";

    while ( fgets(buf, sizeof(buf), stream) != NULL )
        output += buf;
    fclose(stream);

    return output;
}

/* **********************************************
 * ***** GET PERCENTAGE FROM COMMAND OUTPUT *****
 * **********************************************
 */

/* Return program command output as a percentage */
int AtlasCommand::get_cmd_percent(std::string cmd)
{
    std::string output = exec_cmd(cmd);
    size_t      len    = output.length();
    std::string level;
    size_t      i;

    for ( i = 0; (i < len) && (level.length() <= 3); ++i ) {
        if ( !isdigit(output[i]) ) {
            if ( level.compare("") == 0 )
                continue;
            else
                break;
        }

        level += output[i];
    }

    int percent = atoi(level.c_str());
    return (percent <= 100) ? percent : 100;
}
