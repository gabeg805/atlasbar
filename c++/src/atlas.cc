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
#include "Statusbar.h"
#include "AtlasApple.h"
#include "AtlasUserApp.h"
#include <gtkmm.h>
#include <iostream>

std::vector<NameApp*> container;

/* ************************************************************************** */
/* Display Atlas Statusbar */
int main(int argc, char **argv)
{
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");

    static Statusbar atlas;
    atlas.init();
    atlas.new_app("[battery]",    get_battery_icon);
    atlas.new_app("[wifi]",       get_wifi_icon,       wifi_event);
    atlas.new_app("[volume]",     get_volume_icon,     volume_signal);
    atlas.new_app("[brightness]", get_brightness_icon, brightness_signal);
    atlas.new_app("[date]",       get_date_text);
    atlas.new_app("[workspace]",  get_workspace_text,  workspace_signal);
    atlas.show_all_children();

    return app->run(atlas);
}
