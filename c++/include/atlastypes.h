/* *****************************************************************************
 * 
 * Name:    atlastypes.h
 * Type:    <_AtlasAppType>, <_AtlasUserAppType>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Application and User Application types.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_TYPES_H
#define ATLAS_TYPES_H

/* Includes */
#include "atlasalign.h"
#include "atlasfunc.h"
#include <stdint.h>
#include <string>

/* Structures */
/* Atlas application type */
struct _AtlasAppType
{
    std::string     name;
    std::string     type;
    atlas::align_t  align;
    uint8_t         length;
    int             focus;
    uint32_t        signal;
    atlas::func_t  *func;
    void           *widget;
};
/* Atlas user application type */
struct _AtlasUserAppType
{
    std::string   name;
    uint32_t      signal;
    atlas::func_t func;
};

/* Namespace Extension */
namespace atlas
{
    typedef _AtlasAppType     app_t;
    typedef _AtlasUserAppType uapp_t;
};

#endif /* ATLAS_TYPES_H */
