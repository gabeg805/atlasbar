/* *****************************************************************************
 * 
 * Name:    Brightness.h
 * Class:   <Brightness>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas brightness indicator application.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_BRIGHTNESS_H
#define ATLAS_BRIGHTNESS_H

/* Includes */
#include "AtlasApp.h"
#include <gtkmm.h>
#include <string>

/* Classes */
class Brightness:
    public AtlasApp<Gtk::Image>
{
public:
    void               create(void);
    static bool        update(void *w);
    static std::string get_icon(void);
};

/* Global object */
extern Brightness brightness;

#endif /* ATLAS_BRIGHTNESS_H */
