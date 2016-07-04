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
#include "atlastypes.h"
#include "AtlasAppUtil.h"
#include "AtlasSignalType.h"
#include "atlasio.h"
#include <fcntl.h>
#include <semaphore.h>
#include <stdint.h>
#include <sys/stat.h>
#include <csignal>
#include <string>
#include <vector>
std::vector<atlas::app_t*> atlasevent::container;


#include <iostream>

#include "atlasipc.h"

/* ************************************************************************** */
/* Update an app by their name*/
void atlasevent::signal(int sig)
{
    std::cout << "Received the signal!" << std::endl;

    /* Retrieve value from semaphore */
    // sem_t *sem = sem_open("/semi", O_RDONLY, 0644, 0);
    // if ( sem == NULL )
    //     return;

    // uint32_t key;
    // sem_getvalue(sem, (int*)&key);
    // // uint8_t atlaskey = barkey(xkey);
    int      fd  = initipc();
    std::cout << "fd: " << fd << std::endl;
    uint32_t data = rdipc(fd);

    std::cout << "data: 0x" << std::hex << data << std::endl;

    // std::cout << "xsig: 0x" << std::hex << xkey << std::endl;
    // std::cout << "asig: 0x" << std::hex << (atlaskey & ATLAS_SIG_MASK) << std::endl
        ;
    std::vector<atlas::app_t*>::iterator app;
    uint32_t appsig;
    uint32_t datakey;

    /* Update statusbar and call application command */
    for ( app=atlasevent::container.begin();
          app != atlasevent::container.end();
          ++app )
    {
        // if ( (*app)->func->signal != NULL ) {
        //     int ret = (*app)->func->signal(key);
        //     if ( ret == 0 )
        //         atlasevent::update(*app);
        //     else if ( ret > 0 )
        //         atlasevent::update(*app, ret);
        //     else
        //         ;
        // }
        std::cout << "name: " << (*app)->name << " | appsig: 0x" << std::hex << (*app)->signal << std::endl;
        appsig  = (*app)->signal;
        datakey = (data & ATLAS_SIG_MASK);
        if ( (appsig != 0) && (appsig == datakey) ) {
            uint32_t ret = (*app)->func->signal(data);
            std::cout << "ret:  0x" << std::hex << ret << std::endl;
            if ( ret == ATLAS_SIG_DONE )
                atlasevent::update(*app);
            else
                atlasevent::update(*app, ret);
        }
    }
}

/* ************************************************************************** */
/* Update an application */
bool atlasevent::update(atlas::app_t *app)
{
    if ( app == NULL )
        return false;

    std::string type = app->type; 
    if ( type.compare("image") == 0 )
        atlas::app::util::set_image(app);
    else if ( type.compare("label") == 0 )
        atlas::app::util::set_label(app);
    else
        return false;

    // atlasio::debug("Updated '"+app->name+"'.");
    return true;
}        

/* ************************************************************************** */
/* Update an application */
bool atlasevent::update(atlas::app_t *app, int ret)
{
    atlas::app::util::set_focus(app, ret);
    atlasio::debug("Set focus: '"+std::to_string(ret)+"'.");
    return atlasevent::update(app);
}
