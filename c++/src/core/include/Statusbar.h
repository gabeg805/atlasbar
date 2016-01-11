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
#ifndef CORE_ATLAS_STATUSBAR_H
#define CORE_ATLAS_STATUSBAR_H

/* Includes */
#include "AtlasApple.h"
#include <gtkmm.h>

/* Classes */
class Statusbar:
    public Gtk::Window,
    public AtlasApple
{
public:
    Statusbar();
    void init(void);
    void build(void);

    Gtk::Box *widget;
};

#endif /* CORE_ATLAS_STATUSBAR_H */
