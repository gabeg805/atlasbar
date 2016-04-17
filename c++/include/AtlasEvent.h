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
    int  doimage(atlas::app *node, int val);
    int  dolabel(atlas::app *node, int val);
    bool update(atlas::app *node);
    bool update(atlas::app *node, int val);

    extern std::vector<atlas::app*> container;
};


#endif /* ATLAS_EVENT_H */
