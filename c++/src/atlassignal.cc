/* *****************************************************************************
 * 
 * Name:      atlassignal.cc
 * Namespace: <atlas::signal>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: The Atlas signal handler.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlassignal.h"
#include "atlasglobals.h"
#include "atlasipc.h"
#include "atlaskeys.h"
#include "atlasutil.h"
#include <stdint.h>

/* ************************************************************************** */
/* Update an app by their name*/
void atlas::signal::handler(int sig)
{
    int      fd      = initipc();
    uint32_t data    = rdipc(fd);
    uint32_t datakey = (data & ATLAS_SIG_MASK);
    uint32_t appkey;
    atlas::clbk_t  callback;
    atlas::vecit_t app;
    atlasprintf(LOG, "Received signal: 0x%0X", data);

    for ( app=atlas::signal::container.begin();
          app != atlas::signal::container.end();
          ++app )
    {
        /* Execute callback function for given signal */
        appkey = (*app).get_key();
        if ( appkey == datakey ) {
            atlasprintf(LOG, "Executing signal handler for matched app.");
            callback = (*app).get_signal();
            callback(data);
            break;
        }
    }
}
