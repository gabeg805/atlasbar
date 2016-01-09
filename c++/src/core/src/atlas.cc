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
// #include "Battery.h"
// #include "Wifi.h"
// #include "Volume.h"
// #include "Brightness.h"
// #include "Date.h"
// #include "Workspace.h"
#include "AtlasUserApp.h"
#include <gtkmm.h>

#include "AtlasApple.h"

/* Declares */
// Volume     volume;
// Brightness brightness;
// Workspace  workspace;

NameApp *head = NULL;

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

    atlas.init();
    atlas.creation("[battery]",    get_battery_icon);
    atlas.creation("[wifi]",       get_wifi_icon,       wifi_event);
    atlas.creation("[volume]",     get_volume_icon,     NULL,       volume_signal);
    atlas.creation("[brightness]", get_brightness_icon, NULL,       brightness_signal);
    atlas.creation("[date]",       get_date_text);
    /* atlas.creation("[workspace]", get_workspace); */
    atlas.build();
    atlas.show_all_children();

    return app->run(atlas);
}
