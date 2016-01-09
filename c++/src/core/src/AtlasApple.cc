#include "AtlasApple.h"
#include "AtlasConfig.h"
#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>

#include "AtlasUserApp.h"

#include <stdint.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <cstdlib>

/* ************************************************************************** */
/* Update applications */
bool update_app(NameApp *node)
{
    Gtk::Widget *app = AtlasApple::get_app(node);
    std::string type = node->type;
    if ( type.compare("image") == 0 )
        static_cast<Gtk::Image*>(app)->set(node->getstr());
    else if ( type.compare("label") == 0 )
        static_cast<Gtk::Label*>(app)->set_text(node->getstr());
    else
        ;

    return true;
}        

/* ************************************************************************** */
/* Constructor */
AtlasApple::AtlasApple()
{
}

/* ************************************************************************** */
/* Return the head of the application linked list */
NameApp * AtlasApple::get_head(void)
{
    return head;
}

/* ************************************************************************** */
/* Allocate space for, and return, the next available node */
NameApp * AtlasApple::get_node(void)
{
    NameApp *node;
    if ( head == NULL ) {
        head = new NameApp();
        node = head;
    }
    else {
        node = head; /* assign this initially */
        while ( node->next != NULL )
            node = node->next;

        node->next = new NameApp();
        node       = node->next;
    }

    AtlasApple::clear_node(node);
    return node;
}

/* ************************************************************************** */
/* Return the application corresponding to the given node */
Gtk::Widget * AtlasApple::get_app(NameApp *node)
{
    std::string event = AtlasConfig::fetch(node->name, "event");
    if ( event.empty() )
        return static_cast<Gtk::Widget*>(node->app);
    else
        return static_cast<Gtk::EventBox*>(node->app)->get_child();
}

/* ************************************************************************** */
/* Update an app by their name*/
int AtlasApple::update(std::string name)
{
    NameApp *node = head;
    while ( node != NULL ) {
        if ( name.compare(node->name) == 0 ) {
            update_app(node);
            return 0;
        }
        node = node->next;
    }
    return 1;
}

/* ************************************************************************** */
/* Update an app by their name*/
void AtlasApple::signal(int sig)
{
    /* Retrieve value from semaphore */
    sem_t        *sem = sem_open("/semi", O_RDONLY, 0644, 0);
    unsigned int  key;
    unsigned int  val;
    if ( sem == NULL )
        return;
    else
        sem_getvalue(sem, (int*)&key);

    FILE *fp = fopen("/home/gabeg/.config/dwm/stuffers.txt", "a+");
    fprintf(fp, "sig: 0x%0x\n", key);

    /* Update statusbar and call application command */
    NameApp *node = head;
    while ( node != NULL ) {
        if ( node->signal != NULL )
            node->signal(key);
        node = node->next;
    }

    fclose(fp);
}

/* ************************************************************************** */
/* Set the name of the node */
int AtlasApple::set_name(NameApp *node, std::string name)
{
    node->name = name;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" function of the node */
int AtlasApple::set_func(NameApp *node, std::string (*getstr)(void))
{
    node->getstr = getstr;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" and "event" functions of the node */
int AtlasApple::set_func(NameApp *node, std::string (*getstr)(void), bool (*event)(void*))
{
    node->getstr = getstr;
    node->event  = event;
    return 0;
}

/* ************************************************************************** */
/* Set the "get", "event", and "signal" functions of the node */
int AtlasApple::set_func(NameApp *node, std::string (*getstr)(void), bool (*event)(void*), bool (*signal)(unsigned int))
{
    node->getstr = getstr;
    node->event  = event;
    node->signal = signal;
    return 0;
}

/* ************************************************************************** */
/* Set the type of the node */
int AtlasApple::set_type(NameApp *node)
{
    node->type = AtlasConfig::fetch(node->name, "type");
    return 0;
}

/* ************************************************************************** */
/* Generalized function to initialize and set the application */
int AtlasApple::set_app(void **app, std::string type, std::string str)
{
    if ( type.compare("image") == 0 )
        *app = new Gtk::Image(str);
    else if ( type.compare("label") == 0 )
        *app = new Gtk::Label(str);
    else
        return -1;

    return 0;
}


/* ************************************************************************** */
/* Initialize and set the application */
int AtlasApple::set_app(NameApp *node)
{
    if ( node->name.empty() )
        return -1;

    void *app;
    AtlasApple::set_app(&app, node->type, node->getstr());
    if ( node->event == NULL )
        node->app = app;
    else {
        node->app = new Gtk::EventBox();
        static_cast<Gtk::Container*>(node->app)->add(*static_cast<Gtk::Widget*>(app));

        std::string event = AtlasConfig::fetch(node->name, "event");
        if ( event.compare("hover") == 0 )
            static_cast<Gtk::EventBox*>(node->app)->signal_enter_notify_event().connect(sigc::ptr_fun(node->event));
    }

    return 0;
}

/* ************************************************************************** */
/* Set the application alignment */
int AtlasApple::set_align(NameApp *node)
{
    std::string align = AtlasConfig::fetch(node->name, "align");
    if ( align.empty() )
        return -1;

    if ( align.compare("left") == 0 )
        node->align = AtlasAlign::LEFT;
    else if ( (align.compare("center") == 0) || align.compare("middle") == 0 )
        node->align = AtlasAlign::CENTER;
    else if ( align.compare("right") == 0 )
        node->align = AtlasAlign::RIGHT;
    else
        node->align = AtlasAlign::RIGHT;
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasApple::set_length(NameApp *node)
{
    unsigned int length = AtlasConfig::fetch_int(node->name, "length");
    if ( length == 0 )
        ++length;
    node->length = length;
    return 0;
}

/* ************************************************************************** */
/* Set the application to update/refresh every given number of seconds */
int AtlasApple::set_update(NameApp *node)
{
    int time = AtlasConfig::fetch_int(node->name, "update");
    if ( time <= 0 )
        return -1;

    sigc::slot<bool, NameApp*> slot = sigc::ptr_fun(update_app);
    Glib::signal_timeout().connect_seconds(sigc::bind<NameApp*>(slot, node), time);
    return 0;
}

/* ************************************************************************** */
/* Set the application x-y margins */
int AtlasApple::set_margin(NameApp *node)
{
    std::string margin = AtlasConfig::fetch(node->name, "margin");
    if ( margin.empty() )
        return -1;

    int          xmargin = atoi(AtlasConfig::cut(margin, 1, ',').c_str());
    int          ymargin = atoi(AtlasConfig::cut(margin, 2, ',').c_str());
    Gtk::Widget *app     = static_cast<Gtk::Widget*>(node->app);
    if ( node->event != NULL )
        app = static_cast<Gtk::EventBox*>(node->app)->get_child();

    app->set_margin_start(xmargin);
    app->set_margin_end(xmargin);
    app->set_margin_top(ymargin);
    app->set_margin_bottom(ymargin);
    return 0;
}

/* ************************************************************************** */
/* Set the application x-y padding */
int AtlasApple::set_padding(NameApp *node)
{
    std::string padding = AtlasConfig::fetch(node->name, "padding");
    if ( padding.empty() )
        return -1;

    int        xpadding = atoi(AtlasConfig::cut(padding, 1, ',').c_str());
    int        ypadding = atoi(AtlasConfig::cut(padding, 2, ',').c_str());
    Gtk::Misc *app      = static_cast<Gtk::Misc*>(node->app);
    if ( node->event != NULL )
        app = static_cast<Gtk::Misc*>(static_cast<Gtk::EventBox*>(node->app)->get_child());

    app->set_padding(xpadding, ypadding);
    return 0;
}

/* ************************************************************************** */
/* Set the application background */
int AtlasApple::set_background(NameApp *node)
{
    std::string background = AtlasConfig::fetch(node->name, "background");
    if ( background.empty() )
        return -1;

    Gtk::Widget *app = static_cast<Gtk::Widget*>(node->app);
    if ( node->event != NULL )
        app = static_cast<Gtk::EventBox*>(node->app)->get_child();

    Gdk::RGBA color(background);
    app->override_background_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the application foreground */
int AtlasApple::set_foreground(NameApp *node)
{
    std::string foreground = AtlasConfig::fetch(node->name, "foreground");
    if ( foreground.empty() )
        return -1;

    Gtk::Widget *app = static_cast<Gtk::Widget*>(node->app);
    if ( node->event != NULL )
        app = static_cast<Gtk::EventBox*>(node->app)->get_child();

    Gdk::RGBA color(foreground);
    app->override_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the application font */
int AtlasApple::set_font(NameApp *node)
{
    std::string font = AtlasConfig::fetch(node->name,     "font");
    int         size = AtlasConfig::fetch_int(node->name, "font-size");
    if ( font.empty() && (size <= 0) )
        return -1;

    Gtk::Widget *app = static_cast<Gtk::Widget*>(node->app);
    if ( node->event != NULL )
        app = static_cast<Gtk::EventBox*>(node->app)->get_child();

    Pango::FontDescription fd;
    if ( !font.empty() )
        fd.set_family(font);
    if ( size > 0 )
        fd.set_size(size * PANGO_SCALE);


    app->override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Clear the node structure */
NameApp * AtlasApple::clear_node(NameApp *node)
{
    node->name   = "";
    node->type   = "";
    node->align  = AtlasAlign::NONE;
    node->length = 0;
    node->getstr = NULL;
    node->event  = NULL;
    node->signal = NULL;
    node->app    = NULL;
    node->next   = NULL;
    return node;
}

/* ************************************************************************** */
/* Create an application (no event and no signal) */
void AtlasApple::creation(std::string name, std::string (*getstr)(void))
{
    AtlasApple::creation(name, getstr, NULL);
}

/* ************************************************************************** */
/* Create an application (event and no signal) */
void AtlasApple::creation(std::string name, std::string (*getstr)(void), bool (*event)(void*))
{
    AtlasApple::creation(name, getstr, event, NULL);
}

/* ************************************************************************** */
/* Create an application (event and signal) */
void AtlasApple::creation(std::string name, std::string (*getstr)(void), bool (*event)(void*), bool (*signal)(unsigned int))
{
    if ( !AtlasConfig::exists(name) )
        return;

    NameApp *node = AtlasApple::get_node();
    AtlasApple::set_name(node, name);
    AtlasApple::set_func(node, getstr, event, signal);
    AtlasApple::set_type(node);
    AtlasApple::set_app(node);
    AtlasApple::set_align(node);
    AtlasApple::set_background(node);
    AtlasApple::set_foreground(node);
    AtlasApple::set_font(node);
    AtlasApple::set_length(node);
    AtlasApple::set_margin(node);
    AtlasApple::set_padding(node);
    AtlasApple::set_update(node);
}

    // // std::string text      = AtlasConfig::fetch(name,     "text");
    // // std::string format    = AtlasConfig::fetch(name,     "format");
