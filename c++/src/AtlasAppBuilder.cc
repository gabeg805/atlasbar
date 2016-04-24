/* *****************************************************************************
 * 
 * Name:    AtlasAppBuilder.h
 * Class:   <AtlasAppBuilder>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Application builder. Creates an Atlas App by reading
 *              information in the configuration file.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasAppBuilder.h"
#include "AtlasApp.h"
#include "AtlasAppUtil.h"
#include "AtlasFunc.h"
#include "atlasio.h"
#include <stdint.h>
#include <string.h>
#include <cstdlib>
#include <string>

/* Globals */
// atlas::uapp *AtlasUserAppBuilder::uapps;

/* ************************************************************************** */
/* Constructor */
AtlasAppBuilder::AtlasAppBuilder()
{
    this->app = NULL;
}

/* ************************************************************************** */
/* Reallocate memory for applications */
void AtlasAppBuilder::alloc(uint8_t num)
{
    // uint8_t size = (num+1)*sizeof(atlas::app);
    // this->uapps  = (atlas::uapp*) realloc(this->uapps, size);
    // memset(this->uapps, 0, size);
}

// /* ************************************************************************** */
// /* Create a new app */
// void AtlasUserAppBuilder::new_app(std::string name, atlas::func func)
// {
//     static uint8_t  index   = 0;
//     static uint8_t *length  = reinterpret_cast<uint8_t*>(this->uapps-1);
//     this->uapps[index].name = name;
//     this->uapps[index].func = func;
//     (*length)++;
//     index++;
// }

/* ************************************************************************** */
/* Create an application (event and signal) */
void AtlasAppBuilder::create(std::string name, atlas::func *func)
{
    if ( !AtlasAppUtil::is_app(name) )
        return;
    AtlasAppUtil::new_app(&this->app); /* Change this to init_app */
    AtlasAppUtil::set_name(this->app, name);
    AtlasAppUtil::set_func(this->app, func);
    AtlasAppUtil::set_type(this->app);
    AtlasAppUtil::set_length(this->app);
    AtlasAppUtil::set_focus(this->app);
    AtlasAppUtil::set_align(this->app);
    AtlasAppUtil::set_widget(this->app);
    AtlasAppUtil::set_update(this->app);
    atlasio::debug("Created application '"+name+"'.");
}



/* ************************************************************************** */
/* Constructor */
AtlasUserAppBuilder::AtlasUserAppBuilder(uint8_t num)
{
    this->uapps = (atlas::uapp*) calloc(num+1, sizeof(atlas::uapp));
    this->uapps++;
}

/* ************************************************************************** */
/* Reallocate memory for applications */
void AtlasUserAppBuilder::alloc(uint8_t num)
{
    uint8_t size = (num+1)*sizeof(atlas::uapp);
    this->uapps--;
    this->uapps  = (atlas::uapp*) realloc(this->uapps, size);
    memset(this->uapps, 0, size);
    this->uapps++;
}

/* ************************************************************************** */
/* Create a new user app */
void AtlasUserAppBuilder::new_uapp(std::string name, atlas::func func)
{
    static uint8_t  index   = 0;
    static uint8_t *length  = reinterpret_cast<uint8_t*>(this->uapps-1);
    this->uapps[index].name = name;
    this->uapps[index].func = func;
    (*length)++;
    index++;
}

/* ************************************************************************** */
/* Return app container */
atlas::uapp * AtlasUserAppBuilder::get_uapps(void)
{
    return this->uapps;
}
