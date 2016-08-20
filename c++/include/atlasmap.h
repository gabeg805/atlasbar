/* *****************************************************************************
 * 
 * Name:      atlasmap.h
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: The Atlas map container for storing pairs of signal keys and
 *              atlas applications. Used for calling an applications respective
 *              signal with ease.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_MAP_H
#define ATLAS_MAP_H

/* Includes */
#include "atlasapp.h"
#include "atlassignal.h"
#include <map>


/* Namespace */
namespace atlas
{
    /* Typedefs */
    typedef std::map<key_t, AtlasApp> map_t;
    typedef map_t::iterator           mapiter_t;
};

#endif /* ATLAS_MAP_H */
