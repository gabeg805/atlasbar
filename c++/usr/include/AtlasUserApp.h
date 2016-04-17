/* *****************************************************************************
 * 
 * Name:    AtlasUserApp.h
 * Class:   None
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas User Application type.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_USER_APP_H
#define ATLAS_USER_APP_H

/* Includes */
#include "AtlasFunc.h"
#include <string>

/* Structure */
struct AtlasUserApp
{
    std::string  name;
    AtlasFunc    func;
};

#endif /* ATLAS_USER_APP_H */
