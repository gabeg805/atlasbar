/* *****************************************************************************
 * 
 * Name:    atlasapp.h
 * Class:   <AtlasApp>
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
#ifndef ATLAS_APP_H
#define ATLAS_APP_H

/* Includes */
#include "atlastypes.h"
#include "atlasfunc.h"
#include <stdint.h>
#include <string>

/* Classes */
/* Atlas application */
class AtlasApp
{
public:
    AtlasApp(uint8_t num);
    void           alloc(uint8_t num);
    void           new_app(std::string name, atlas::func_t *func, uint32_t signal);
    atlas::app_t * get_app(void);

    atlas::app_t *apps;
};
/* Atlas user application */
class AtlasUserApp
{
public:
    AtlasUserApp(uint8_t num);
    void            alloc(uint8_t num);
    void            new_uapp(std::string name, atlas::func_t func, uint32_t signal);
    atlas::uapp_t * get_uapps(void);

private:
    atlas::uapp_t *uapps;
};

#endif /* ATLAS_APP_H */
