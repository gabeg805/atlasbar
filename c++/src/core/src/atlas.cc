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

/* ************************************************************************** */
/* Display Atlas Statusbar */
int main(int argc, char** argv)
{
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");

    static Statusbar atlas;
    atlas.init();
    atlas.create("[battery]",    get_battery_icon);
    atlas.create("[wifi]",       get_wifi_icon,       wifi_event);
    atlas.create("[volume]",     get_volume_icon,     NULL,       volume_signal);
    atlas.create("[brightness]", get_brightness_icon, NULL,       brightness_signal);
    atlas.create("[date]",       get_date_text);
    atlas.create("[workspace]",  get_workspace_text,  NULL,       workspace_signal);
    atlas.build();
    atlas.show_all_children();

    return app->run(atlas);
}
