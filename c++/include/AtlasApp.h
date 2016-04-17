/* *****************************************************************************
 * 
 * Name:    AtlasApp.h
 * Class:   None
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas application type.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_APP_H
#define ATLAS_APP_H

/* Includes */
#include "AtlasAlignType.h"
#include "AtlasFunc.h"
#include <stdint.h>
#include <string>

/* Structure */
struct NameApp {
    std::string             name;
    std::string             type;
    AtlasAlign::AlignType   align;
    uint8_t                 length;
    int                     focus;
    AtlasFunc              *func;
    void                   *widget;
};

#endif /* ATLAS_APP_H */
