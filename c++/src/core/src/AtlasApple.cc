#include "AtlasApple.h"
#include "AtlasAppGeneric.h"
#include "AtlasConfig.h"
#include "AtlasEvent.h"
#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "AtlasUserApp.h"

/* ************************************************************************** */
/* Constructor */
AtlasApple::AtlasApple()
{
    this->app = NULL;
}

/* ************************************************************************** */
/* Create an application (no event and no signal) */
void AtlasApple::create(std::string name, AtlasGetFunc getstr)
{
    AtlasApple::create(name, getstr, NULL, NULL);
}

/* ************************************************************************** */
/* Create an application (event and no signal) */
void AtlasApple::create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event)
{
    AtlasApple::create(name, getstr, event, NULL);
}

/* ************************************************************************** */
/* Create an application (signal and no event) */
void AtlasApple::create(std::string name, AtlasGetFunc getstr, AtlasSignalFunc signal)
{
    AtlasApple::create(name, getstr, NULL, signal);
}

/* ************************************************************************** */
/* Create an application (event and signal) */
void AtlasApple::create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
{
    if ( !AtlasConfig::exists(name) ) {
        std::cout << "No application with name '" + name + "' in config file." << std::endl;
        return;
    }

    AtlasApple::new_app();
    AtlasAppGeneric::set_name(this->app, name);
    AtlasAppGeneric::set_func(this->app, getstr, event, signal);
    AtlasAppGeneric::set_type(this->app);
    AtlasAppGeneric::set_length(this->app);
    AtlasAppGeneric::set_focus(this->app);
    AtlasAppGeneric::set_align(this->app);
    AtlasApple::set_widget();
    AtlasAppGeneric::set_update(this->app);
}



/* ************************************************************************** */
/* Allocate space for a new application */
int AtlasApple::new_app(void)
{
    this->app = new NameApp();
    AtlasAppGeneric::clear(this->app);
    return 0;
}

/* ************************************************************************** */
/* Initialize and set an image application */
int AtlasApple::set_image(void **widget)
{
    Gtk::Image               *img        = static_cast<Gtk::Image*>(*widget);
    std::vector<std::string>  strvec     = AtlasConfig::parse(this->app->getstr(), '|');
    std::string               name       = this->app->name;
    int                       len        = this->app->length;
    std::string               margin     = AtlasConfig::fetch(name, "margin");
    std::string               padding    = AtlasConfig::fetch(name, "padding");
    std::string               background = AtlasConfig::fetch(name, "background");
    std::string               foreground = AtlasConfig::fetch(name, "foreground");
    int i;
    for ( i = 0; i < len; ++i ) {
        img[i].set(strvec[i]);
        AtlasAppGeneric::set_margin(img[i], margin);
        AtlasAppGeneric::set_padding(img[i], padding);
        AtlasAppGeneric::set_background(img[i], background);
        AtlasAppGeneric::set_foreground(img[i], foreground);
    }

    return 0;
}


/* ************************************************************************** */
/* Initialize and set an image application */
int AtlasApple::init_widget(void **widget)
{
    std::string type = this->app->type;
    int         len  = this->app->length;
    if ( type.compare("image") == 0 )
        *widget = new Gtk::Image[len];
    else if ( type.compare("label") == 0 )
        *widget = new Gtk::Label[len];
    else
        return -1;
    return 0;
}

/* ************************************************************************** */
/* Initialize and set the application */
int AtlasApple::set_widget(void)
{
    if ( this->app->name.empty() )
        return -1;

    void *widget;
    AtlasApple::init_widget(&widget);
    AtlasApple::set_widget(&widget);
    if ( this->app->event == NULL )
        this->app->app = widget;
    else {
        this->app->app = new Gtk::EventBox();
        static_cast<Gtk::Container*>(this->app->app)->add(*static_cast<Gtk::Widget*>(widget));

        std::string event = AtlasConfig::fetch(this->app->name, "event");
        if ( event.compare("hover") == 0 )
            static_cast<Gtk::EventBox*>(this->app->app)->signal_enter_notify_event().connect(sigc::ptr_fun(this->app->event));
    }

    return 0;
}

/* ************************************************************************** */
/* Generalized function to initialize and set the application */
int AtlasApple::set_widget(void **widget)
{
    std::string type = this->app->type;
    if ( type.compare("image") == 0 )
        AtlasApple::set_image(widget);
    else if ( type.compare("label") == 0 )
        AtlasEvent::set_label(app, widget);
    else
        return -1;

    return 0;
}
