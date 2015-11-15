/* *****************************************************************************
 * 
 * Name:    Statusbar.cc
 * Class:   <Statusbar>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas status bar - contains all status bar applications.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "Statusbar.h"
#include "AtlasConfig.h"
#include "StatusSignal.h"
#include <gtkmm.h>
#include <gdkmm.h>
#include <cstdlib>
#include <csignal>
#include <string>

/* ************************************************************************** */
/* Construct the Atlas status bar */
Statusbar::Statusbar():
    Gtk::Window(Gtk::WINDOW_POPUP),
    AtlasApp(new Gtk::Box())
{
    set_title("Atlas");
    signal(SIGUSR1, StatusSignal::statusSigCatcher);
}

/* ************************************************************************** */
/* Create Atlas status bar */
void Statusbar::create(void)
{
    int         width       = AtlasConfig::fetch_int("width");
    int         height      = AtlasConfig::fetch_int("height");
    std::string orientation = AtlasConfig::fetch("orientation");
    std::string background  = AtlasConfig::fetch("background");
    std::string foreground  = AtlasConfig::fetch("foreground");
    Gdk::RGBA   back(background);
    Gdk::RGBA   fore(foreground);

    set_default_size(width, height);
    // set_orientation(orientation);
    override_background_color(back, Gtk::STATE_FLAG_NORMAL);
    override_color(fore, Gtk::STATE_FLAG_NORMAL);
    add(*this->widget);
}
