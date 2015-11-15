/* *****************************************************************************
 * 
 * Name:    Volume.h
 * Class:   <Volume>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas volume indicator application.
 *              
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_VOLUME_H
#define ATLAS_VOLUME_H

/* Includes */
#include "AtlasApp.h"
#include <gtkmm.h>
#include <string>

/* Classes */
class Volume:
    public AtlasApp<Gtk::Image>
{
public:
    void               create(void);
    static bool        update(void *w);
    static std::string get_icon(void);
};

/* Global object */
extern Volume volume;

#endif /* ATLAS_VOLUME_H */
