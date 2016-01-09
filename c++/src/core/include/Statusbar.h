/* *****************************************************************************
 * 
 * Name:    Statusbar.h
 * Class:   <Statusbar>
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
#include "AtlasApple.h"
#include <gtkmm.h>

/* Classes */
class Statusbar:
    public Gtk::Window,
    public AtlasApp<Gtk::Box>,
    public AtlasApple
{
public:
    Statusbar();
    void init(void);
    void build(void);
};

#endif /* ATLAS_STATUSBAR_H */
