/* *****************************************************************************
 * 
 * Name:    AtlasApp.h
 * Type:    <AtlasApp>, <AtlasUserApp>
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
#ifndef ATLAS_APP_H
#define ATLAS_APP_H

/* Includes */
#include "AtlasAlign.h"
#include "AtlasFunc.h"
#include <stdint.h>
#include <string>

/* Structures */
/* Atlas application */
struct AtlasApp
{
    std::string   name;
    std::string   type;
    atlas::align  align;
    uint8_t       length;
    int           focus;
    atlas::func  *func;
    void         *widget;
};
/* Atlas user application */
struct AtlasUserApp
{
    std::string name;
    atlas::func func;
};

/* Namespace Extension */
namespace atlas
{
    typedef AtlasApp     app;
    typedef AtlasUserApp uapp;
};

#endif /* ATLAS_APP_H */
