/* *****************************************************************************
 * 
 * Name:    atlas.h
 * Class:   <atlas>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas program header include. A simple way for a user to
 *              include all necessary Atlas header files.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_H
#define ATLAS_H

/* Includes */
#include "Statusbar.h"
#include <string>

/* Namespace */
namespace atlas
{
    extern std::string prog;
}

#include "AtlasAlign.h"
#include "AtlasApp.h"
#include "AtlasFunc.h"

#endif /* ATLAS_H */
