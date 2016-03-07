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
#include "AtlasAppLib.h"
#include <gtkmm.h>

/* Class */
class Statusbar:
    public Gtk::Window,
    public AtlasApp
{
public:
    Statusbar();
    void init(void);
    void new_app(std::string name, AtlasGetFunc getstr);
    void new_app(std::string name, AtlasGetFunc getstr, AtlasEventFunc event);
    void new_app(std::string name, AtlasGetFunc getstr, AtlasSignalFunc signal);
    void new_app(std::string name, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal);

private:
    int attach(NameApp *app);

    Gtk::Box *statusbar;
};

#endif /* ATLAS_STATUSBAR_H */
