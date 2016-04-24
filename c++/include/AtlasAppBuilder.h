/* *****************************************************************************
 * 
 * Name:    AtlasAppBuilder.h
 * Class:   <AtlasAppBuilder>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Application builder.
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
#include <stdint.h>
#include <string>

/* Classes */
/* Atlas application builder */
class AtlasAppBuilder
{
public:
    AtlasAppBuilder();

    void alloc(uint8_t num);
    void create(std::string name, atlas::func *func);

    atlas::app *app;
};
/* Atlas user application builder */
class AtlasUserAppBuilder
{
public:
    AtlasUserAppBuilder(uint8_t num);
    void          alloc(uint8_t num);
    void          new_uapp(std::string name, atlas::func func);
    atlas::uapp * get_uapps(void);

private:
    atlas::uapp *uapps;
};

#endif /* ATLAS_APP_H */
