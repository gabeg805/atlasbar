/* *****************************************************************************
 * 
 * Name:    atlas.cc
 * Class:   main()
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Syntax: $ g++ -g -Wall -o atlas *.cc `pkg-config gtkmm-3.0 --cflags --libs`
 *         $ ./atlas
 * 
 * Description: The Atlas Status Bar.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasApp.h"
#include "AtlasAlignType.h"
#include "Statusbar.h"
#include "Battery.h"
#include "Wifi.h"
#include "Volume.h"
#include "Brightness.h"
#include "Date.h"
#include "Workspace.h"
#include <gtkmm.h>

/* Declares */
Volume     volume;
Brightness brightness;
Workspace  workspace;

/* ***********************************
 * ***** DISPLAY ATLAS STATUSBAR *****
 * ***********************************
 */

int main(int argc, char** argv)
{
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");

    static Statusbar atlas;
    static Battery   battery;
    static Wifi      wifi;
    static Date      date;

    atlas.create();
    battery.create();
    wifi.create();
    volume.create();
    brightness.create();
    date.create();
    workspace.create();

    atlas.attach(battery,    AtlasAlign::RIGHT);
    atlas.attach(wifi,       AtlasAlign::RIGHT);
    atlas.attach(volume,     AtlasAlign::RIGHT);
    atlas.attach(brightness, AtlasAlign::RIGHT);
    atlas.attach(date,       AtlasAlign::CENTER);
    atlas.attach(workspace,  AtlasAlign::LEFT);
    atlas.show_all_children();

    return app->run(atlas);
}
