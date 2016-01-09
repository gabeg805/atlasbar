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
    AtlasApp(new Gtk::Box()),
    AtlasApple()
{
    this->set_title("Atlas");
    std::signal(SIGUSR1, AtlasApple::signal);
}

/* ************************************************************************** */
/* Create Atlas status bar */
void Statusbar::init(void)
{
    std::string o  = AtlasConfig::fetch("[main]", "orientation");
    Gtk::Orientation orientation;
    if ( o.compare("horizontal") == 0 )
        orientation = Gtk::ORIENTATION_HORIZONTAL;
    else if ( o.compare("vertical") == 0 )
        orientation = Gtk::ORIENTATION_VERTICAL;
    else
        orientation = Gtk::ORIENTATION_HORIZONTAL;

    std::string bg = AtlasConfig::fetch("[main]", "background");
    std::string fg = AtlasConfig::fetch("[main]", "foreground");
    Gdk::RGBA   background(bg);
    Gdk::RGBA   foreground(fg);
    int         width       = AtlasConfig::fetch_int("[main]", "width");
    int         height      = AtlasConfig::fetch_int("[main]", "height");

    this->set_default_size(width, height);
    this->widget->set_orientation(orientation);
    this->override_background_color(background, Gtk::STATE_FLAG_NORMAL);
    this->override_color(foreground,            Gtk::STATE_FLAG_NORMAL);
    this->add(*this->widget);
}

/* ************************************************************************** */
/* Attach apps to the Atlas status bar */
void Statusbar::build(void)
{
    if ( !dynamic_cast<Gtk::Container*>(this->widget) ) {
        std::cout << "this->widget is not a container" << std::endl;
        return;
    }

    NameApp *node = AtlasApple::get_head();
    size_t   i;
    size_t   len;
    while ( node != NULL ) {
        len = node->length;
        std::cout << "Loop: " << node->name << std::endl;

        switch ( node->align ) {
        case AtlasAlign::NONE:
            break;
        case AtlasAlign::LEFT:
            for ( i = 0; i < len; ++i )
                static_cast<Gtk::Box*>(this->widget)->pack_start(*static_cast<Gtk::Widget*>(node->app), Gtk::PACK_SHRINK);
            break;
        case AtlasAlign::CENTER:
            for ( i = 0; i < len; ++i )
                static_cast<Gtk::Box*>(this->widget)->set_center_widget(*static_cast<Gtk::Widget*>(node->app));
            break;
        case AtlasAlign::RIGHT:
            for ( i = 0; i < len; ++i )
                static_cast<Gtk::Box*>(this->widget)->pack_end(*static_cast<Gtk::Widget*>(node->app), Gtk::PACK_SHRINK);
            break;
        }

        node = node->next;
    }
}
