/* *****************************************************************************
 * 
 * Name:      atlascmdutil.cc
 * Namespace: <atlas::cmd>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: An Atlas utility for executing commands and parsing command
 *              output.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlascmdutil.h"
#include <ctype.h>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <string>

/* ************************************************************************** */
/* Execute the specified command and return the output */
std::string atlas::cmd::exec(std::string cmd)
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

/* ************************************************************************** */
/* Execute the command and treat the output as a percentage (0-100) */
int atlas::cmd::get_percent(std::string cmd)
{
    std::string output = atlas::cmd::exec(cmd);
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
