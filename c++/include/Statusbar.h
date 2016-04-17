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
#include "AtlasApp.h"
#include "AtlasAppBuilder.h"
#include "AtlasFunc.h"
#include <gtkmm.h>
#include <string>

/* Class */
class Statusbar:
    public Gtk::Window,
    public AtlasAppBuilder
{
public:
    Statusbar();

    void create(void);
    void new_app(std::string, atlas::func *func);

private:
    void init(void);
    int  attach(atlas::app *app);

    Gtk::Box *statusbar;
};

#endif /* ATLAS_STATUSBAR_H */
