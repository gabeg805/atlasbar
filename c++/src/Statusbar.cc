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
#include "atlastypes.h"
#include "atlasapp.h"
#include "AtlasAppUtil.h"
#include "atlasalign.h"
#include "atlasevent.h"
#include "atlasfunc.h"
#include "atlasio.h"
#include "atlasipc.h"
#include "atlasuser.h"
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
    AtlasApp(0)
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
    atlas::app::util::set_orientation(*this->statusbar,  o);
    atlas::app::util::set_background(*this->statusbar,  bg);
    atlas::app::util::set_foreground(*this->statusbar,  fg);
    atlas::app::util::set_size(*this, width, height);

    this->set_title("Atlas");
    this->add(*this->statusbar);

    initipc();
    std::signal(SIGIO, atlasevent::signal);

    atlasio::debug("Initialized Atlas Status Bar.");
}

/* ************************************************************************** */
/* Create the Atlas Status Bar */
void Statusbar::create(void)
{
    atlas::uapp_t *uapps  = create_user_apps();
    uint8_t        length = reinterpret_cast<uint8_t&>(*(uapps-1));
    uint8_t        i;
    this->alloc(length);
    for ( i=0; i < length; ++i ) {
        this->new_app(uapps[i].name, &uapps[i].func, uapps[i].signal);
        this->attach(this->get_app());
    }
    this->show_all_children();
    atlasio::debug("Created status bar.");
}

/* ************************************************************************** */
/* Attach an Atlas application to the statusbar */
int Statusbar::attach(atlas::app_t *app)
{
    Gtk::Widget    *widget = atlas::app::util::get_widget(app->widget, app->type);
    atlas::align_t  align  = app->align;
    size_t          len    = app->length;
    size_t          i;

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
