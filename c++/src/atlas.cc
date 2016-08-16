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

/* Global */
std::string  atlas::prog = "atlas";
atlas::vec_t atlas::signal::container;

/* ************************************************************************** */
/* Display Atlas Statusbar */
int main(int argc, char **argv)
{
    Glib::RefPtr<Gtk::Application> app =
        Gtk::Application::create(argc, argv,
                                 "org.gtkmm.examples.base");

    static AtlasStatusBar atlas;
    atlas.create();
    return app->run(atlas);
}
