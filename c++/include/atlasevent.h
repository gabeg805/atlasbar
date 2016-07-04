/* *****************************************************************************
 * 
 * Name:      atlasevent.h
 * Namespace: <atlasevent>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: The Atlas event handler. Once a signal is raised, the event
 *              handler will update the Statusbar in the appropriate manner.
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_EVENT_H
#define ATLAS_EVENT_H

/* Includes */
#include "atlastypes.h"
#include <vector>

/* Namespace */
namespace atlasevent
{
    void signal(int sig);
    bool update(atlas::app_t *node);
    bool update(atlas::app_t *node, int val);

    extern std::vector<atlas::app_t*> container;
};


#endif /* ATLAS_EVENT_H */
