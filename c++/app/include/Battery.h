/* *****************************************************************************
 * 
 * Name:    Battery.h
 * Class:   <Battery>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas battery indicator application.
 *              
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header Guard */
#ifndef ATLAS_BATTERY_H
#define ATLAS_BATTERY_H

/* Includes */
#include "AtlasApp.h"
#include <gtkmm.h>
#include <string>

class Battery:
    public AtlasApp<Gtk::Image>
{
public:
    void               create(void);
    static bool        update(void *w);
    static std::string get_icon(void);
};

#endif /* ATLAS_BATTERY_H */
