/* *****************************************************************************
 * 
 * Name:    StatusBar.h
 * Class:   <StatusBar>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Status Bar container.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_STATUSBAR_H
#define ATLAS_STATUSBAR_H

/* Includes */
#include "atlastypes.h"
#include "atlasapp.h"
#include "atlasfunc.h"
#include <gtkmm.h>
#include <string>

/* Class */
class Statusbar:
    public Gtk::Window,
    public AtlasApp
{
public:
    Statusbar();
    void create(void);

private:
    void init(void);
    int  attach(atlas::app_t *app);

    Gtk::Box *statusbar;
};

#endif /* ATLAS_STATUSBAR_H */
