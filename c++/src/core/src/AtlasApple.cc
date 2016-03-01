#include "AtlasApple.h"
#include "AtlasAppGeneric.h"
#include "AtlasConfig.h"
#include <stdint.h>
#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "AtlasUserApp.h"

#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>

/* ************************************************************************** */
/* Constructor */
AtlasApple::AtlasApple()
{
    app = NULL;
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
    AtlasApple::set_name(name);
    AtlasApple::set_func(getstr, event, signal);
    AtlasApple::set_type();
    AtlasApple::set_length();
    AtlasApple::set_focus();
    AtlasApple::set_align();
    AtlasApple::set_widget();
    AtlasApple::set_update();
}

/* ************************************************************************** */
/* Update an app by their name*/
void AtlasApple::signal(int sig)
{
    /* Retrieve value from semaphore */
    sem_t        *sem = sem_open("/semi", O_RDONLY, 0644, 0);
    unsigned int  key;
    if ( sem == NULL )
        return;
    else
        sem_getvalue(sem, (int*)&key);

    FILE *fp = fopen("/home/gabeg/.config/dwm/stuffers.txt", "a+");
    fprintf(fp, "sig: 0x%0x\n", key);

    /* Update statusbar and call application command */
    // uint8_t i;
    // for ( i = 0; i < size; ++i ) {
    //     if ( container[i]->signal != NULL ) {
    //         int ret = container[i]->signal(key);
    //         if ( ret == 0 )
    //             update(container[i]);
    //         else if ( ret > 0 )
    //             update(container[i], ret);
    //         else
    //             ;
    //     }
    // }

    fclose(fp);
}

/* ************************************************************************** */
/* Update applications */
bool AtlasApple::update(NameApp *node)
{
    return AtlasApple::update(node, 0);
}        

/* ************************************************************************** */
/* Update applications */
bool AtlasApple::update(NameApp *node, int ret)
{
    if ( node == NULL )
        return false;

    std::string type = node->type;
    if ( type.compare("image") == 0 )
        AtlasApple::doimage(node, ret);
    else if ( type.compare("label") == 0 )
        AtlasApple::dolabel(node, ret);
    else
        ;

    return true;
}

int AtlasApple::doimage(NameApp *node, int ret)
{
    if ( ret == 0 ) {
        Gtk::Widget              *app = AtlasApple::get_widget(node);
        std::vector<std::string>  vec = AtlasConfig::parse(node->getstr(), '|');
        int                       len = node->length;
        int                       i;
        for ( i = 0; i < len; ++i )
            static_cast<Gtk::Image*>(app)[i].set(vec[i]);
        return 0;
    }

    return 0;
}

int AtlasApple::dolabel(NameApp *node, int ret)
{
    std::cout << "doing label: " << node->name << std::endl;
    std::cout << "setting focus: " << ret << std::endl;
    AtlasApple::set_focus(node, ret);
    AtlasApple::set_label(node);
    std::cout << "Workspace: " << ret << std::endl;

    return 0;
}

/* ************************************************************************** */
/* Return the application corresponding to the given node */
Gtk::Widget * AtlasApple::get_widget(NameApp *node)
{
    if ( node == NULL )
        return NULL;

    std::string event = AtlasConfig::fetch(node->name, "event");
    if ( event.empty() )
        return static_cast<Gtk::Widget*>(node->app);
    else
        return static_cast<Gtk::EventBox*>(node->app)->get_child();
}

/* ************************************************************************** */
/* Allocate space for a new application */
int AtlasApple::new_app(void)
{
    app = new NameApp();
    AtlasApple::clear();
    return 0;
}

/* ************************************************************************** */
/* Set the name of the node */
int AtlasApple::set_name(std::string name)
{
    app->name = name;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" function of the node */
int AtlasApple::set_func(AtlasGetFunc getstr)
{
    app->getstr = getstr;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" and "event" functions of the node */
int AtlasApple::set_func(AtlasGetFunc getstr, AtlasEventFunc event)
{
    app->getstr = getstr;
    app->event  = event;
    return 0;
}

/* ************************************************************************** */
/* Set the "get", "event", and "signal" functions of the node */
int AtlasApple::set_func(AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
{
    app->getstr = getstr;
    app->event  = event;
    app->signal = signal;
    return 0;
}

/* ************************************************************************** */
/* Set the type of the node */
int AtlasApple::set_type(void)
{
    app->type = AtlasConfig::fetch(app->name, "type");
    return 0;
}

/* ************************************************************************** */
/* Initialize and set an image application */
int AtlasApple::set_image(void **widget)
{
    Gtk::Image               *img        = static_cast<Gtk::Image*>(*widget);
    std::vector<std::string>  strvec     = AtlasConfig::parse(app->getstr(), '|');
    std::string               name       = app->name;
    int                       len        = app->length;
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
/* Initialize and set a label application */
int AtlasApple::set_label(NameApp *node)
{
    void *widget = AtlasApple::get_widget(node);
    return AtlasApple::set_label(node, &widget);
}

/* ************************************************************************** */
/* Initialize and set a label application */
int AtlasApple::set_label(NameApp *node, void **widget)
{
    Gtk::Label               *label       = static_cast<Gtk::Label*>(*widget);
    std::string               name        = node->name;
    int                       len         = node->length;
    int                       focus       = node->focus;
    std::vector<std::string>  strvec      = AtlasConfig::parse(node->getstr(), '|');
    std::string               font        = AtlasConfig::fetch(name, "font");
    int                       size        = AtlasConfig::fetch_int(name, "font-size");
    std::string               margin      = AtlasConfig::fetch(name, "margin");
    std::string               padding     = AtlasConfig::fetch(name, "padding");
    std::string               background  = AtlasConfig::fetch(name, "background");
    std::string               foreground  = AtlasConfig::fetch(name, "foreground");
    std::string               focus_color = AtlasConfig::fetch(name, "focus-color");
    int i;
    for ( i = 0; i < len; ++i ) {
        label[i].set_text(strvec[i]);
        AtlasAppGeneric::set_font(label[i], font, size);
        AtlasAppGeneric::set_margin(label[i], margin);
        AtlasAppGeneric::set_padding(label[i], padding);
        AtlasAppGeneric::set_background(label[i], background);
        AtlasAppGeneric::set_foreground(label[i], foreground);
        set_focuser(label[i], i, focus, focus_color);
    }

    return 0;
}

/* ************************************************************************** */
int AtlasApple::set_focuser(Gtk::Widget &widget, int index, int focus, std::string color)
{
    if ( focus < 0 )
        return -1;
    else {
        if ( index == focus )
            AtlasAppGeneric::set_foreground(widget, color);
        else
            return -1;
    }
    return 0;
}

/* ************************************************************************** */
/* Initialize and set an image application */
int AtlasApple::init_widget(void **widget)
{
    std::string type = app->type;
    int         len  = app->length;
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
    if ( app->name.empty() )
        return -1;

    void *widget;
    AtlasApple::init_widget(&widget);
    AtlasApple::set_widget(&widget);
    if ( app->event == NULL )
        app->app = widget;
    else {
        app->app = new Gtk::EventBox();
        static_cast<Gtk::Container*>(app->app)->add(*static_cast<Gtk::Widget*>(widget));

        std::string event = AtlasConfig::fetch(app->name, "event");
        if ( event.compare("hover") == 0 )
            static_cast<Gtk::EventBox*>(app->app)->signal_enter_notify_event().connect(sigc::ptr_fun(app->event));
    }

    return 0;
}

/* ************************************************************************** */
/* Generalized function to initialize and set the application */
int AtlasApple::set_widget(void **widget)
{
    std::string type = app->type;
    if ( type.compare("image") == 0 )
        AtlasApple::set_image(widget);
    else if ( type.compare("label") == 0 )
        AtlasApple::set_label(app, widget);
    else
        return -1;

    return 0;
}

/* ************************************************************************** */
/* Set the application alignment */
int AtlasApple::set_align(void)
{
    std::string align = AtlasConfig::fetch(app->name, "align");
    if ( align.empty() )
        return -1;

    if ( align.compare("left") == 0 )
        app->align = AtlasAlign::LEFT;
    else if ( (align.compare("center") == 0) || align.compare("middle") == 0 )
        app->align = AtlasAlign::CENTER;
    else if ( align.compare("right") == 0 )
        app->align = AtlasAlign::RIGHT;
    else
        app->align = AtlasAlign::RIGHT;
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasApple::set_length(void)
{
    unsigned int length = AtlasConfig::fetch_int(app->name, "length");
    if ( length == 0 )
        ++length;
    app->length = length;
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasApple::set_focus(void)
{
    std::string str = AtlasConfig::fetch(app->name, "focus");
    if ( str.empty() )
        app->focus = -1;
    else
        app->focus = atoi(str.c_str());
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasApple::set_focus(NameApp *node, int index)
{
    node->focus = index;
    return 0;
}

/* ************************************************************************** */
/* Set the application to update/refresh every given number of seconds */
int AtlasApple::set_update(void)
{
    int time = AtlasConfig::fetch_int(app->name, "update");
    if ( time <= 0 )
        return -1;

    sigc::slot<bool, NameApp*> slot = sigc::ptr_fun((bool (*)(NameApp*))update);
    Glib::signal_timeout().connect_seconds(sigc::bind<NameApp*>(slot, app), time);
    return 0;
}

/* ************************************************************************** */
/* Clear the node structure */
int AtlasApple::clear(void)
{
    app->name   = "";
    app->type   = "";
    app->align  = AtlasAlign::NONE;
    app->length = 0;
    app->getstr = NULL;
    app->event  = NULL;
    app->signal = NULL;
    app->app    = NULL;
    return 0;
}
