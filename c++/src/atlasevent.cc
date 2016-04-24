/* *****************************************************************************
 * 
 * Name:    atlasevent.cc
 * Class:   <atlasevent>
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
#include "atlasevent.h"
#include "AtlasApp.h"
#include "AtlasAppUtil.h"
#include "atlasio.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdint.h>
#include <sys/stat.h>
#include <string>
#include <vector>

std::vector<atlas::app*> atlasevent::container;

/* ************************************************************************** */
/* Update an app by their name*/
void atlasevent::signal(int sig)
{
    /* Retrieve value from semaphore */
    sem_t *sem = sem_open("/semi", O_RDONLY, 0644, 0);
    if ( sem == NULL )
        return;

    uint16_t key;
    sem_getvalue(sem, (int*)&key);
    std::vector<atlas::app*>::iterator app;

    /* Update statusbar and call application command */
    for ( app=atlasevent::container.begin();
          app != atlasevent::container.end();
          ++app )
    {
        if ( (*app)->func->signal != NULL ) {
            int ret = (*app)->func->signal(key);
            if ( ret == 0 )
                atlasevent::update(*app);
            else if ( ret > 0 )
                atlasevent::update(*app, ret);
            else
                ;
        }
    }
}

/* ************************************************************************** */
/* Update an application */
bool atlasevent::update(atlas::app *app)
{
    if ( app == NULL )
        return false;

    std::string type = app->type; 
    if ( type.compare("image") == 0 )
        AtlasAppUtil::set_image(app);
    else if ( type.compare("label") == 0 )
        AtlasAppUtil::set_label(app);
    else
        return false;

    atlasio::debug("Updated '"+app->name+"'.");
    return true;
}        

/* ************************************************************************** */
/* Update an application */
bool atlasevent::update(atlas::app *app, int ret)
{
    AtlasAppUtil::set_focus(app, ret);
    return atlasevent::update(app);
}
