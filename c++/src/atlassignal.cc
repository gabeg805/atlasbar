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
#include "atlasmap.h"
#include "atlasutil.h"
#include <stdint.h>

/* ************************************************************************** */
/* Update an app by their name*/
void atlas::signal::handler(int sig)
{
    int      fd   = openipc();
    uint32_t data = readipc(fd);
    uint32_t key  = (data & ATLAS_SIG_MASK);
    atlasprintf(LOG, "Received signal: 0x%0X", data);

    /* Find signal key match */
    atlas::mapiter_t search = atlas::signal::container.find(key);
    if ( search == atlas::signal::container.end() ) {
        atlasprintf(LOG, "Signal not found in container.");
        return;
    }
    /* Execute callback */
    atlas::sig_t *signal = search->second.get_signal();
    signal->callback(data);
}
