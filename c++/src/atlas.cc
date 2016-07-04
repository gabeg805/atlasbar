/* *****************************************************************************
 * 
 * Name:    atlas.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas program.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlas.h"
#include <gtkmm.h>

/* Global */
std::string atlas::prog = "atlas";

/* ************************************************************************** */
/* Display Atlas Statusbar */
int main(int argc, char **argv)
{
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");

    static Statusbar atlas;
    atlas.create();
    return app->run(atlas);
}
