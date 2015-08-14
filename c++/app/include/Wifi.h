/* *****************************************************************************
 * 
 * Name:    Wifi.h
 * Class:   <Wifi>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas wifi indicator application.
 *              
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_WIFI_H
#define ATLAS_WIFI_H

/* Includes */
#include "AtlasApp.h"
#include <gtkmm.h>
#include <string>

/* Classes */
class Wifi:
    public AtlasApp<Gtk::Image>
{
public:
    void               create(void);
    static bool        update(void *w);
    static std::string get_icon(void);
};

#endif /* ATLAS_WIFI_H */
