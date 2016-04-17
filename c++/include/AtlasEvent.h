/* *****************************************************************************
 * 
 * Name:      AtlasEvent.h
 * Namespace: <AtlasEvent>
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
#include "AtlasApp.h"
#include <vector>

/* Namespace */
namespace AtlasEvent
{
    void signal(int sig);
    int  doimage(NameApp *node, int val);
    int  dolabel(NameApp *node, int val);
    bool update(NameApp *node);
    bool update(NameApp *node, int val);

    extern std::vector<NameApp*> container;
};


#endif /* ATLAS_EVENT_H */
