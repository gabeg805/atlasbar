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
#include "AtlasAppBuilder.h"
#include "AtlasAppUtil.h"
#include "AtlasAlignType.h"
#include "AtlasEvent.h"
#include "AtlasFunc.h"
#include "atlasio.h"
#include "AtlasUser.h"
#include "AtlasUserApp.h"
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
    AtlasAppBuilder()
{
    this->statusbar = new Gtk::Box();
    this->init();
}

/* ************************************************************************** */
/* Initialize the Atlas Status Bar */
void Statusbar::init(void)
{
    std::string o      = AtlasConfig::fetch("statusbar",     "orientation");
    std::string bg     = AtlasConfig::fetch("statusbar",     "background");
    std::string fg     = AtlasConfig::fetch("statusbar",     "foreground");
    int         width  = AtlasConfig::fetch_int("statusbar", "width");
    int         height = AtlasConfig::fetch_int("statusbar", "height");
    AtlasAppUtil::set_orientation(*this->statusbar, o);
    AtlasAppUtil::set_background(*this->statusbar, bg);
    AtlasAppUtil::set_foreground(*this->statusbar, fg);
    AtlasAppUtil::set_size(*this, width, height);

    this->set_title("Atlas");
    this->add(*this->statusbar);
    std::signal(SIGUSR1, AtlasEvent::signal);

    atlasio::debug("Initialized Atlas Status Bar.");
}

/* ************************************************************************** */
/* Create the Atlas Status Bar */
void Statusbar::create(void)
{
    AtlasUserApp *user_apps = create_user_apps();
    uint8_t       i;
    if ( user_apps == NULL )
        return;
    for ( i=0; !user_apps[i].name.empty(); ++i )
        this->new_app(user_apps[i].name, &user_apps[i].func);
    this->show_all_children();
    atlasio::debug("Created status bar.");
}

/* ************************************************************************** */
/* Create an application (event and signal) */
void Statusbar::new_app(std::string name, AtlasFunc *func)
{
    AtlasAppBuilder *app = new AtlasAppBuilder();
    app->create(name, func);
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
    case AtlasAlign::NONE: {
        } break;
    case AtlasAlign::LEFT: {
        Gtk::Label *labs = static_cast<Gtk::Label*>(app->widget);
        for ( i = 0; i < len; ++i )
            this->statusbar->pack_start(static_cast<Gtk::Widget&>(labs[i]), Gtk::PACK_SHRINK);
        } break;
    case AtlasAlign::CENTER: {
        for ( i = 0; i < len; ++i )
            this->statusbar->set_center_widget(*static_cast<Gtk::Widget*>(app->widget));
        } break;
    case AtlasAlign::RIGHT: {
        for ( i = 0; i < len; ++i )
            this->statusbar->pack_end(*static_cast<Gtk::Widget*>(app->widget), Gtk::PACK_SHRINK);
        } break;
    default:
        return -1;
    }
    return 0;
}
