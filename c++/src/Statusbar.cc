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
#include "AtlasApp.h"
#include "AtlasAppUtil.h"
#include "AtlasEvent.h"
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
    AtlasApp()
{
    this->statusbar = new Gtk::Box();
}

/* ************************************************************************** */
/* Create Atlas status bar */
void Statusbar::init(void)
{
    std::string o      = AtlasConfig::fetch("[main]",     "orientation");
    std::string bg     = AtlasConfig::fetch("[main]",     "background");
    std::string fg     = AtlasConfig::fetch("[main]",     "foreground");
    int         width  = AtlasConfig::fetch_int("[main]", "width");
    int         height = AtlasConfig::fetch_int("[main]", "height");

    AtlasAppUtil::set_orientation(*this->statusbar, o);
    AtlasAppUtil::set_background(*this->statusbar, bg);
    AtlasAppUtil::set_foreground(*this->statusbar, fg);
    AtlasAppUtil::set_size(*this, width, height);

    this->set_title("Atlas");
    this->add(*this->statusbar);
    std::signal(SIGUSR1, AtlasEvent::signal);
}

/* ************************************************************************** */
/* Create an application (no event and no signal) */
void Statusbar::new_app(std::string name, AtlasGetFunc getstr)
{
    Statusbar::new_app(name, getstr, NULL, NULL);
}

/* ************************************************************************** */
/* Create an application (event and no signal) */
void Statusbar::new_app(std::string name, AtlasGetFunc getstr, AtlasEventFunc event)
{
    Statusbar::new_app(name, getstr, event, NULL);
}

/* ************************************************************************** */
/* Create an application (signal and no event) */
void Statusbar::new_app(std::string name, AtlasGetFunc getstr, AtlasSignalFunc signal)
{
    Statusbar::new_app(name, getstr, NULL, signal);
}

/* ************************************************************************** */
/* Create an application (event and signal) */
void Statusbar::new_app(std::string name, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
{
    AtlasApp *app = new AtlasApp();
    app->create(name, getstr, event, signal);
    Statusbar::attach(app->app);
}

/* ************************************************************************** */
/* Attach an Atlas application to the statusbar */
int Statusbar::attach(NameApp *app)
{
    AtlasEvent::container.push_back(app);

    size_t len = app->length;
    size_t i;
    switch ( app->align ) {
    case AtlasAlign::NONE:
        break;
    case AtlasAlign::LEFT:
        Gtk::Label *labs;
        labs = static_cast<Gtk::Label*>(app->app);
        for ( i = 0; i < len; ++i )
            this->statusbar->pack_start(static_cast<Gtk::Widget&>(labs[i]), Gtk::PACK_SHRINK);
        break;
    case AtlasAlign::CENTER:
        for ( i = 0; i < len; ++i )
            this->statusbar->set_center_widget(*static_cast<Gtk::Widget*>(app->app));
        break;
    case AtlasAlign::RIGHT:
        for ( i = 0; i < len; ++i )
            this->statusbar->pack_end(*static_cast<Gtk::Widget*>(app->app), Gtk::PACK_SHRINK);
        break;
    default:
        return -1;
    }
    return 0;
}
