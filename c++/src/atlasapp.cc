/* *****************************************************************************
 * 
 * Name:    atlasapp.cc
 * Class:   <AtlasApp>
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
#include "atlasapp.h"
#include "atlastypes.h"
#include "AtlasAppUtil.h"
#include "atlasfunc.h"
#include "atlasio.h"
#include <stdint.h>
#include <string.h>
#include <strings.h>
#include <cstdlib>
#include <string>

/* ************************************************************************** */
/* Constructor */
AtlasApp::AtlasApp(uint8_t num)
{
    this->apps = new atlas::app_t[num+1];
    uint8_t *length = reinterpret_cast<uint8_t*>(this->apps);
    *length = 0;
    this->apps++;
}

#include <iostream>

/* ************************************************************************** */
/* Reallocate memory for applications */
void AtlasApp::alloc(uint8_t num)
{
    this->apps--;
    this->apps      = new atlas::app_t[num+1];
    uint8_t *length = reinterpret_cast<uint8_t*>(this->apps);
    *length         = 0;
    this->apps++;
}

/* ************************************************************************** */
/* Create a new application */
void AtlasApp::new_app(std::string name, atlas::func_t *func, uint32_t signal)
{
    static uint8_t  index  = 0;
    static uint8_t *length = reinterpret_cast<uint8_t*>(this->apps-1);
    if ( !atlas::app::util::is_app(name) )
        return;

    atlas::app_t *app = &this->apps[index];
    atlas::app::util::set_name(app, name);
    atlas::app::util::set_func(app, func);
    atlas::app::util::set_signal(app, signal);
    atlas::app::util::set_type(app);
    atlas::app::util::set_length(app);
    atlas::app::util::set_focus(app);
    atlas::app::util::set_align(app);
    atlas::app::util::set_widget(app);
    atlas::app::util::set_update(app);
    (*length)++;
    index++;
    atlasio::debug("Created application '"+name+"'.");
}

/* ************************************************************************** */
/* Return the newest application */
atlas::app_t * AtlasApp::get_app(void)
{
    uint8_t length = reinterpret_cast<uint8_t&>(*(this->apps-1));
    return &this->apps[length-1];
}



/* ************************************************************************** */
/* Constructor */
AtlasUserApp::AtlasUserApp(uint8_t num)
{
    this->uapps = (atlas::uapp_t*) calloc(num+1, sizeof(atlas::uapp_t));
    this->uapps++;
}

/* ************************************************************************** */
/* Reallocate memory for applications */
void AtlasUserApp::alloc(uint8_t num)
{
    uint8_t size = (num+1)*sizeof(atlas::uapp_t);
    this->uapps--;
    this->uapps  = (atlas::uapp_t*) realloc(this->uapps, size);
    memset(this->uapps, 0, size);
    this->uapps++;
}

/* ************************************************************************** */
/* Create a new user app */
void AtlasUserApp::new_uapp(std::string name, atlas::func_t func, uint32_t signal)
{
    static uint8_t  index     = 0;
    static uint8_t *length    = reinterpret_cast<uint8_t*>(this->uapps-1);
    this->uapps[index].name   = name;
    this->uapps[index].func   = func;
    this->uapps[index].signal = signal;
    (*length)++;
    index++;
}

/* ************************************************************************** */
/* Return app container */
atlas::uapp_t * AtlasUserApp::get_uapps(void)
{
    return this->uapps;
}
