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
#include "atlasconf.h"
#include "AtlasApp.h"
#include "AtlasAppBuilder.h"
#include "AtlasAppUtil.h"
#include "AtlasAlign.h"
#include "atlasevent.h"
#include "AtlasFunc.h"
#include "atlasio.h"
#include "AtlasUser.h"
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
    std::string o      = atlasconf::find("statusbar",     "orientation");
    std::string bg     = atlasconf::find("statusbar",     "background");
    std::string fg     = atlasconf::find("statusbar",     "foreground");
    int         width  = atlasconf::find_int("statusbar", "width");
    int         height = atlasconf::find_int("statusbar", "height");
    AtlasAppUtil::set_orientation(*this->statusbar,  o);
    AtlasAppUtil::set_background(*this->statusbar,  bg);
    AtlasAppUtil::set_foreground(*this->statusbar,  fg);
    AtlasAppUtil::set_size(*this, width, height);

    this->set_title("Atlas");
    this->add(*this->statusbar);
    std::signal(SIGUSR1, atlasevent::signal);

    atlasio::debug("Initialized Atlas Status Bar.");
}

/* ************************************************************************** */
/* Create the Atlas Status Bar */
void Statusbar::create(void)
{
    atlas::uapp *uapps  = create_user_apps();
    // this->apps
    uint8_t      length = reinterpret_cast<uint8_t&>(*(uapps-1));
    uint8_t      i;
    for ( i=0; i < length; ++i )
        this->new_app(uapps[i].name, &uapps[i].func);
    this->show_all_children();
    atlasio::debug("Created status bar.");
}

/* I say that I (statusbar) am an atlasappbuilder but I don't utilize it Maybe
 * jsut hae the creation in th constructor (for both builders) Also have app
 * builder give a size so that I know and there's consistencty for both
 * builders */

/* ************************************************************************** */
/* Create an application (event and signal) */
void Statusbar::new_app(std::string name, atlas::func *func)
{
    AtlasAppBuilder *app = new AtlasAppBuilder();
    app->create(name, func);
    Statusbar::attach(app->app);
}

/* ************************************************************************** */
/* Attach an Atlas application to the statusbar */
int Statusbar::attach(atlas::app *app)
{
    Gtk::Widget  *widget = AtlasAppUtil::get_widget(app->widget, app->type);
    atlas::align  align  = app->align;
    size_t        len    = app->length;
    size_t        i;

    /* Set widget on status bar */
    if ( align == atlas::align::NONE )
        ;
    else if ( align == atlas::align::LEFT )
        for ( i = 0; i < len; ++i )
            this->statusbar->pack_start(widget[i], Gtk::PACK_SHRINK);
    else if ( align == atlas::align::CENTER )
        for ( i = 0; i < len; ++i )
            this->statusbar->set_center_widget(widget[i]);
    else if ( align == atlas::align::RIGHT )
        for ( i = 0; i < len; ++i )
            this->statusbar->pack_end(widget[i], Gtk::PACK_SHRINK);
    else
        return -1;

    atlasevent::container.push_back(app);
    return 0;
}
