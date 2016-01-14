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
#include "AtlasApple.h"
#include "AtlasAppGeneric.h"
#include <gtkmm.h>
#include <gdkmm.h>
#include <cstdlib>
#include <csignal>
#include <iostream>
#include <string>

/* ************************************************************************** */
/* Construct the Atlas status bar */
Statusbar::Statusbar():
    Gtk::Window(Gtk::WINDOW_POPUP),
    AtlasApple()
{
    this->widget = new Gtk::Box();
}

/* ************************************************************************** */
/* Create Atlas status bar */
void Statusbar::init(void)
{
    std::string o = AtlasConfig::fetch("[main]", "orientation");
    AtlasAppGeneric::set_orientation(*this->widget, o);

    std::string bg = AtlasConfig::fetch("[main]", "background");
    AtlasAppGeneric::set_background(*this->widget, bg);

    std::string fg = AtlasConfig::fetch("[main]", "foreground");
    AtlasAppGeneric::set_foreground(*this->widget, fg);

    int width  = AtlasConfig::fetch_int("[main]", "width");
    int height = AtlasConfig::fetch_int("[main]", "height");
    AtlasAppGeneric::set_size(*this, width, height);

    this->set_title("Atlas");
    this->add(*this->widget);
    std::signal(SIGUSR1, AtlasApple::signal);
}

/* ************************************************************************** */
/* Attach apps to the Atlas status bar */
void Statusbar::build(void)
{
    attach_all_to_parent(this->widget);
}
