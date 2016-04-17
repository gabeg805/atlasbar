/* *****************************************************************************
 * 
 * Name:    AtlasUserAppBuilder.h
 * Class:   <AtlasUserAppBuilder>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas User Application builder.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_USER_APP_BUILDER_H
#define ATLAS_USER_APP_BUILDER_H

/* Includes */
#include "AtlasApp.h"
#include "AtlasFunc.h"
#include <stdint.h>
#include <string>

/* Class */
class AtlasUserAppBuilder
{
public:
    AtlasUserAppBuilder(uint8_t size);

    int           new_app(std::string name, atlas::func func);
    int           remove_app(std::string name);
    int           remove_app(uint8_t i);
    int           clear_app(atlas::uapp *app);
    int           clear_app(uint8_t i);

    atlas::uapp * get_apps(void);
    void          print_apps(void);

private:
    static atlas::uapp *container;
    static uint8_t      index;
};

#endif /* ATLAS_USER_APP_BUILDER_H */
