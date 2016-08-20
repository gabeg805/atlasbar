/* *****************************************************************************
 * 
 * Name:      atlasglobals.h
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: Define globals used by Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_GLOBALS_H
#define ATLAS_GLOBALS_H

/* Includes */
#include "atlassignal.h"
#include "atlasmap.h"

/* Globals */
namespace atlas
{
    extern std::string prog;
    namespace signal { extern atlas::map_t container; };
};

#endif /* ATLAS_GLOBALS_H */
