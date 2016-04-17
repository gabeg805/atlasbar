/* *****************************************************************************
 * 
 * Name:    AtlasAppBuilder.h
 * Class:   <AtlasAppBuilder>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas application builder.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_APP_BUILDER_H
#define ATLAS_APP_BUILDER_H

/* Includes */
#include "AtlasApp.h"
#include "AtlasFunc.h"
#include <string>

/* Class */
class AtlasAppBuilder
{
public:
    AtlasAppBuilder();

    void create (std::string name, AtlasFunc *func);

    NameApp *app;
};

#endif /* ATLAS_APP_H */
