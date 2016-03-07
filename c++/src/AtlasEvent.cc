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
#include "AtlasAppLib.h"
#include "AtlasAppUtil.h"
#include <fcntl.h>
#include <gtkmm.h>
#include <semaphore.h>
#include <stdint.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<NameApp*> AtlasEvent::container;

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
    printf("sig: 0x%0x\n", key);

    /* Update statusbar and call application command */
    std::vector<NameApp*>::iterator app;
    for ( app = AtlasEvent::container.begin(); app != AtlasEvent::container.end(); ++app ) {
        if ( (*app)->signal != NULL ) {
            int ret = (*app)->signal(key);
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
bool AtlasEvent::update(NameApp *node)
{
    return AtlasEvent::update(node, 0);
}        

/* ************************************************************************** */
/* Update applications */
bool AtlasEvent::update(NameApp *node, int ret)
{
    if ( node == NULL )
        return false;

    std::string type = node->type;
    if ( type.compare("image") == 0 )
        AtlasEvent::doimage(node, ret);
    else if ( type.compare("label") == 0 )
        AtlasEvent::dolabel(node, ret);
    else
        ;

    return true;
}

/* ************************************************************************** */
int AtlasEvent::doimage(NameApp *app, int ret)
{
    if ( ret == 0 ) {
        Gtk::Widget              *widget = AtlasAppUtil::get_widget(app);
        std::vector<std::string>  vec    = AtlasConfig::parse(app->getstr(), '|');
        int                       len    = app->length;
        int                       i;
        for ( i = 0; i < len; ++i )
            static_cast<Gtk::Image*>(widget)[i].set(vec[i]);
        return 0;
    }

    return 0;
}

/* ************************************************************************** */
int AtlasEvent::dolabel(NameApp *app, int ret)
{
    std::cout << "doing label: " << app->name << std::endl;
    std::cout << "setting focus: " << ret << std::endl;
    AtlasAppUtil::set_focus(app, ret);
    AtlasAppUtil::set_label(app);
    std::cout << "Workspace: " << ret << std::endl;

    return 0;
}
