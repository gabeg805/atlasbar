/* *****************************************************************************
 * 
 * Name:    atlasstatusbar.cc
 * Class:   <AtlasStatusBar>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas status bar - builds and contains all status bar
 *              applications.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlasstatusbar.h"
#include "atlasalign.h"
#include "atlasapp.h"
#include "atlasapputil.h"
#include "atlasbuilder.h"
#include "atlasglobals.h"
#include "atlasipc.h"
#include "atlassignal.h"
#include "atlasutil.h"
#include <gtkmm.h>
#include <csignal>

/* ************************************************************************** */
/* Construct the Atlas status bar */
AtlasStatusBar::AtlasStatusBar():
    Gtk::Window(Gtk::WINDOW_POPUP)
{
    this->statusbar = new Gtk::Box();
    this->init();
}

/* ************************************************************************** */
/* Initialize the Atlas Status Bar */
void AtlasStatusBar::init(void)
{
    atlas::app::set_orientation(*this->statusbar,  "horizontal");
    atlas::app::set_background(*this->statusbar,  "#333333");
    atlas::app::set_foreground(*this->statusbar,  "#FFFFFF");
    atlas::app::set_size(*this, 1366, 20);

    this->set_title("Atlas");
    this->add(*this->statusbar);

    initipc();
    std::signal(SIGIO, atlas::signal::handler);
    atlasprintf(INFO, "Initialized Atlas Status Bar.");
}

/* ************************************************************************** */
/* Create the Atlas Status Bar */
void AtlasStatusBar::create(void)
{
    AtlasBuilder *builder = app_builder();
    this->attach(builder);
    this->show_all_children();
    atlasprintf(INFO, "Created status bar.");
}

/* ************************************************************************** */
/* Attach an Atlas application to the statusbar */
int AtlasStatusBar::attach(AtlasBuilder *builder)
{
    AtlasApp       app;
    atlas::align_t align;
    int i, j;

    /* Build each application */
    for ( i = 0; builder[i] != NULL; ++i ) {
        app   = builder[i]();
        align = app.get_align();

        /* Attach to statusbar */
        for ( j = 0; j < app.get_size(); ++j ) {
            if ( align == atlas::align::NONE )
                this->statusbar->add(app.get_widget()[j]);
            else if ( align == atlas::align::LEFT )
                this->statusbar->pack_start(app.get_widget()[j], Gtk::PACK_SHRINK);
            else if ( align == atlas::align::CENTER )
                this->statusbar->set_center_widget(app.get_widget()[j]);
            else if ( align == atlas::align::RIGHT )
                this->statusbar->pack_end(app.get_widget()[j], Gtk::PACK_SHRINK);
            else
                return -1;
        }
        /* Add to signal event handler */
        if (app.get_signal() != NULL)
            atlas::signal::container.push_back(app);
    }


    return 0;
}
