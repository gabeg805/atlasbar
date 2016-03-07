/* *****************************************************************************
 * 
 * Name:    AtlasApp.h
 * Class:   <AtlasApp>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas application creater.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasApp.h"
#include "AtlasAppLib.h"
#include "AtlasAppUtil.h"
#include "AtlasConfig.h"
#include <string>

/* ************************************************************************** */
/* Constructor */
AtlasApp::AtlasApp()
{
    this->app = NULL;
}

/* ************************************************************************** */
/* Create an application (no event and no signal) */
void AtlasApp::create(std::string name, AtlasGetFunc getstr)
{
    AtlasApp::create(name, getstr, NULL, NULL);
}

/* ************************************************************************** */
/* Create an application (event and no signal) */
void AtlasApp::create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event)
{
    AtlasApp::create(name, getstr, event, NULL);
}

/* ************************************************************************** */
/* Create an application (signal and no event) */
void AtlasApp::create(std::string name, AtlasGetFunc getstr, AtlasSignalFunc signal)
{
    AtlasApp::create(name, getstr, NULL, signal);
}

/* ************************************************************************** */
/* Create an application (event and signal) */
void AtlasApp::create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
{
    if ( !AtlasConfig::exists(name) )
        return;

    AtlasAppUtil::new_app(&this->app);
    AtlasAppUtil::set_name(this->app, name);
    AtlasAppUtil::set_func(this->app, getstr, event, signal);
    AtlasAppUtil::set_type(this->app);
    AtlasAppUtil::set_length(this->app);
    AtlasAppUtil::set_focus(this->app);
    AtlasAppUtil::set_align(this->app);
    AtlasAppUtil::set_widget(this->app);
    AtlasAppUtil::set_update(this->app);
}
