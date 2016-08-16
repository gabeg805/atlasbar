/* *****************************************************************************
 * 
 * Name:    atlasstatusbar.h
 * Class:   <AtlasStatusBar>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Status Bar.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_STATUSBAR_H
#define ATLAS_STATUSBAR_H

/* Includes */
#include "atlasapp.h"
#include "atlasbuilder.h"
#include <gtkmm.h>

/* Class */
class AtlasStatusBar:
    public Gtk::Window
{
public:
    AtlasStatusBar();
    void create(void);

private:
    void init(void);
    int  attach(AtlasBuilder *builder);

    Gtk::Box *statusbar;
};

#endif /* ATLAS_STATUSBAR_H */
