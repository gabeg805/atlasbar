/* *****************************************************************************
 * 
 * Name:    AtlasEvent.cc
 * Class:   <AtlasEvent>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas event handler.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasEvent.h"
#include "AtlasConfig.h"
#include "AtlasApp.h"
#include "AtlasAppUtil.h"
#include "atlasio.h"
#include <fcntl.h>
#include <gtkmm.h>
#include <semaphore.h>
#include <stdint.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<atlas::app*> AtlasEvent::container;

/* ************************************************************************** */
/* Update an app by their name*/
void AtlasEvent::signal(int sig)
{
    /* Retrieve value from semaphore */
    sem_t *sem = sem_open("/semi", O_RDONLY, 0644, 0);
    if ( sem == NULL )
        return;

    uint16_t key;
    sem_getvalue(sem, (int*)&key);
    std::stringstream stream;
    stream << "sig: 0x" << std::hex << key;
    atlasio::debug(stream.str());

    /* Update statusbar and call application command */
    std::vector<atlas::app*>::iterator app;
    for ( app = AtlasEvent::container.begin(); app != AtlasEvent::container.end(); ++app ) {
        if ( (*app)->func->signal != NULL ) {
            int ret = (*app)->func->signal(key);
            if ( ret == 0 )
                AtlasEvent::update(*app);
            else if ( ret > 0 )
                AtlasEvent::update(*app, ret);
            else
                ;
        }
    }
}

/* ************************************************************************** */
/* Update applications */
bool AtlasEvent::update(atlas::app *app)
{
    return AtlasEvent::update(app, 0);
}        

/* ************************************************************************** */
/* Update applications */
bool AtlasEvent::update(atlas::app *app, int ret)
{
    if ( app == NULL )
        return false;

    std::string type = app->type;
    if ( type.compare("image") == 0 )
        AtlasEvent::doimage(app, ret);
    else if ( type.compare("label") == 0 )
        AtlasEvent::dolabel(app, ret);
    else
        return false;

    atlasio::debug("Updated '"+app->name+"' ("+std::to_string(ret)+").");
    return true;
}

/* ************************************************************************** */
int AtlasEvent::doimage(atlas::app *app, int ret)
{
    if ( ret == 0 ) {
        Gtk::Widget              *widget = AtlasAppUtil::get_widget(app);
        std::vector<std::string>  vec    = AtlasConfig::parse(app->func->info(), '|');
        int                       len    = app->length;
        int                       i;
        for ( i = 0; i < len; ++i )
            static_cast<Gtk::Image*>(widget)[i].set(vec[i]);
        return 0;
    }

    return 0;
}

/* ************************************************************************** */
int AtlasEvent::dolabel(atlas::app *app, int ret)
{
    AtlasAppUtil::set_focus(app, ret);
    AtlasAppUtil::set_label(app);
    return 0;
}
