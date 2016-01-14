#include "AtlasApple.h"
#include "AtlasAppGeneric.h"
#include "AtlasConfig.h"
#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "AtlasUserApp.h"

#include <stdint.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <cstdlib>

NameApp *AtlasApple::head = NULL;

/* ************************************************************************** */
/* Constructor */
AtlasApple::AtlasApple()
{
    // head = NULL;
}

/* ************************************************************************** */
/* Create an application (no event and no signal) */
void AtlasApple::create(std::string name, AtlasGetFunc getstr)
{
    AtlasApple::create(name, getstr, NULL);
}

/* ************************************************************************** */
/* Create an application (event and no signal) */
void AtlasApple::create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event)
{
    AtlasApple::create(name, getstr, event, NULL);
}

/* ************************************************************************** */
/* Create an application (event and signal) */
void AtlasApple::create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
{
    if ( !AtlasConfig::exists(name) )
        return;

    AtlasApple::set_next(&current);
    AtlasApple::set_name(current, name);
    AtlasApple::set_func(current, getstr, event, signal);
    AtlasApple::set_type(current);
    AtlasApple::set_length(current);
    AtlasApple::set_focus(current);
    AtlasApple::set_align(current);
    AtlasApple::set_app(current);
    AtlasApple::set_update(current);
}

/* ************************************************************************** */
/* */
int AtlasApple::attach_all_to_parent(Gtk::Box *parent)
{
    NameApp *node = head;
    while ( node != NULL ) {
        std::cout << "Loop: " << node->name << std::endl;
        AtlasApple::attach_to_parent(*parent, node);
        node = node->next;
    }
    return 0;
}

/* ************************************************************************** */
int AtlasApple::attach_to_parent(Gtk::Box &parent, NameApp *node)
{
    size_t len = node->length;
    size_t i;
    switch ( node->align ) {
    case AtlasAlign::NONE:
        break;
    case AtlasAlign::LEFT:
        Gtk::Label *labs;
        labs = static_cast<Gtk::Label*>(node->app);
        for ( i = 0; i < len; ++i )
            parent.pack_start(static_cast<Gtk::Widget&>(labs[i]), Gtk::PACK_SHRINK);
        break;
    case AtlasAlign::CENTER:
        for ( i = 0; i < len; ++i )
            parent.set_center_widget(*static_cast<Gtk::Widget*>(node->app));
        break;
    case AtlasAlign::RIGHT:
        for ( i = 0; i < len; ++i )
            parent.pack_end(*static_cast<Gtk::Widget*>(node->app), Gtk::PACK_SHRINK);
        break;
    default:
        return -1;
    }
    return 0;
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
    NameApp *node = head;
    while ( node != NULL ) {
        if ( node->signal != NULL ) {
            int ret = node->signal(key);
            if ( ret == 0 )
                update(node);
            else if ( ret > 0 )
                update(node, ret);
            else
                ;
        }
        node = node->next;
    }

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
        Gtk::Widget              *app = AtlasApple::get_app(node);
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
Gtk::Widget * AtlasApple::get_app(NameApp *node)
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
/* Return the application corresponding to the given name */
Gtk::Widget * AtlasApple::get_app(std::string name)
{
    NameApp *node = head;
    while ( node != NULL ) {
        if ( name.compare(node->name) == 0 )
            break;
        node = node->next;
    }
    return AtlasApple::get_app(node);
}

/* ************************************************************************** */
/* Allocate space for, and return, the next available node */
int AtlasApple::set_next(NameApp **node)
{
    if ( head == NULL ) {
        head = new NameApp();
        *node = head;
    }
    else {
        (*node)->next = new NameApp();
        *node         = (*node)->next;
    }

    AtlasApple::clear(node);
    return 0;
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
int AtlasApple::set_func(NameApp *node, AtlasGetFunc getstr)
{
    node->getstr = getstr;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" and "event" functions of the node */
int AtlasApple::set_func(NameApp *node, AtlasGetFunc getstr, AtlasEventFunc event)
{
    node->getstr = getstr;
    node->event  = event;
    return 0;
}

/* ************************************************************************** */
/* Set the "get", "event", and "signal" functions of the node */
int AtlasApple::set_func(NameApp *node, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
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
/* Initialize and set an image application */
int AtlasApple::set_image(NameApp *node, void **app)
{
    Gtk::Image               *img        = static_cast<Gtk::Image*>(*app);
    std::vector<std::string>  strvec     = AtlasConfig::parse(node->getstr(), '|');
    std::string               name       = node->name;
    int                       len        = node->length;
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
    void *app = AtlasApple::get_app(node);
    return AtlasApple::set_label(node, &app);
}

int AtlasApple::set_focuser(Gtk::Widget &app, int index, int focus, std::string color)
{
    if ( focus < 0 )
        return -1;
    else {
        if ( index == focus )
            AtlasAppGeneric::set_foreground(app, color);
        else
            return -1;
    }
    return 0;
}

/* ************************************************************************** */
/* Initialize and set a label application */
int AtlasApple::set_label(NameApp *node, void **app)
{
    Gtk::Label               *label       = static_cast<Gtk::Label*>(*app);
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
/* Generalized function to initialize and set the application */
int AtlasApple::set_app(NameApp *node, void **app)
{
    std::string type = node->type;
    if ( type.compare("image") == 0 )
        AtlasApple::set_image(node, app);
    else if ( type.compare("label") == 0 )
        AtlasApple::set_label(node, app);
    else
        return -1;

    return 0;
}

/* ************************************************************************** */
/* Initialize and set an image application */
int AtlasApple::init_app(NameApp *node, void **app)
{
    std::string type = node->type;
    int         len  = node->length;
    if ( type.compare("image") == 0 )
        *app = new Gtk::Image[len];
    else if ( type.compare("label") == 0 )
        *app = new Gtk::Label[len];
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
    AtlasApple::init_app(node, &app);
    AtlasApple::set_app(node, &app);
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
/* Set the number of sub-applications, within the application */
int AtlasApple::set_focus(NameApp *node)
{
    std::string str = AtlasConfig::fetch(node->name, "focus");
    if ( str.empty() )
        node->focus = -1;
    else
        node->focus = atoi(str.c_str());
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
int AtlasApple::set_update(NameApp *node)
{
    int time = AtlasConfig::fetch_int(node->name, "update");
    if ( time <= 0 )
        return -1;

    sigc::slot<bool, NameApp*> slot = sigc::ptr_fun((bool (*)(NameApp*))update);
    Glib::signal_timeout().connect_seconds(sigc::bind<NameApp*>(slot, node), time);
    return 0;
}

/* ************************************************************************** */
/* Clear the node structure */
int AtlasApple::clear(NameApp **node)
{
    (*node)->name   = "";
    (*node)->type   = "";
    (*node)->align  = AtlasAlign::NONE;
    (*node)->length = 0;
    (*node)->getstr = NULL;
    (*node)->event  = NULL;
    (*node)->signal = NULL;
    (*node)->app    = NULL;
    (*node)->next   = NULL;
    return 0;
}
