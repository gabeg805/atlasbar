#include "AtlasApple.h"
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

    AtlasApple::set_next();
    AtlasApple::set_name(name);
    AtlasApple::set_func(getstr, event, signal);
    AtlasApple::set_type();
    AtlasApple::set_length();
    AtlasApple::set_app();
    AtlasApple::set_align();
    AtlasApple::set_background();
    AtlasApple::set_foreground();
    AtlasApple::set_font();
    AtlasApple::set_margin();
    AtlasApple::set_padding();
    AtlasApple::set_update();
}

    // // std::string text      = AtlasConfig::fetch(name,     "text");
    // // std::string format    = AtlasConfig::fetch(name,     "format");

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
/* Set the background color of an application  */
int AtlasApple::set_background(Gtk::Widget &app, std::string background)
{
    Gdk::RGBA color(background);
    app.override_background_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the foreground color of an application */
int AtlasApple::set_foreground(Gtk::Widget &app, std::string foreground)
{
    Gdk::RGBA color(foreground);
    app.override_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the margin size for an application */
int AtlasApple::set_margin(Gtk::Widget &app, int xmargin, int ymargin)
{
    app.set_margin_start(xmargin);
    app.set_margin_end(xmargin);
    app.set_margin_top(ymargin);
    app.set_margin_bottom(ymargin);
    return 0;
}

/* ************************************************************************** */
/* Set the padding size for an application */
int AtlasApple::set_padding(Gtk::Misc &app, int xpadding, int ypadding)
{
    app.set_padding(xpadding, ypadding);
    return 0;
}

/* ************************************************************************** */
/* Set the font of an application */
int AtlasApple::set_font(Gtk::Widget &app, std::string font)
{
    Pango::FontDescription fd;
    fd.set_family(font);
    app.override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Set the font and text size of an application */
int AtlasApple::set_font(Gtk::Widget &app, std::string font, int size)
{
    Pango::FontDescription fd;
    fd.set_family(font);
    fd.set_size(size * PANGO_SCALE);
    app.override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Set the orientation of an application */
int AtlasApple::set_orientation(Gtk::Orientable &app, std::string orientation)
{
    if ( orientation.compare("vertical") == 0 )
        app.set_orientation(Gtk::ORIENTATION_VERTICAL);
    else if ( orientation.compare("horizontal") == 0 )
        app.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    else
        return -1;
    return 0;
}

/* ************************************************************************** */
int AtlasApple::set_size(Gtk::Window &app, int width, int height)
{
    app.set_default_size(width, height);
    return 0;
}

/* ************************************************************************** */
/* Update applications */
bool AtlasApple::update(NameApp *node)
{
    return AtlasApple::update(node, 0);
    // if ( node == NULL )
    //     return false;

    // Gtk::Widget *app = AtlasApple::get_app(node);
    // std::string type = node->type;
    // if ( type.compare("image") == 0 )
    //     static_cast<Gtk::Image*>(app)->set(node->getstr());
    // else if ( type.compare("label") == 0 )
    //     static_cast<Gtk::Label*>(app)->set_text(node->getstr());
    // else
    //     ;

    // return true;
}        

/* ************************************************************************** */
/* Update applications */
bool AtlasApple::update(NameApp *node, int ret)
{
    if ( node == NULL )
        return false;

    // Gtk::Widget *app = AtlasApple::get_app(node);
    std::string type = node->type;
    if ( type.compare("image") == 0 )
        AtlasApple::doimage(node, ret);
        // static_cast<Gtk::Image*>(app)->set(node->getstr());
    else if ( type.compare("label") == 0 )
        /* static_cast<Gtk::Label*>(app)->set_text(node->getstr()); */
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

    // unsigned int len = node->length;
    // std::string bg_color = AtlasConfig::fetch("workspace_background");
    // std::string hl_color = AtlasConfig::fetch("workspace_highlight");
    // Gdk::RGBA   background(bg_color);
    // Gdk::RGBA   highlight(hl_color);

    // size_t i;
    // for ( i = 0; i < len; ++i ) {
    //     if ( i == (unsigned int)ret )
    //         static_cast<Gtk::Label*>(node->app)[i].override_background_color(highlight, Gtk::STATE_FLAG_NORMAL);
    //     else
    //         static_cast<Gtk::Label*>(node->app)[i].override_background_color(background, Gtk::STATE_FLAG_NORMAL);
    // }

    // std::cout << "Workspace: " << ret << std::endl;

    return 0;
}

int AtlasApple::dolabel(NameApp *node, int ret)
{
    if ( ret == 0 ) {
        Gtk::Widget *app = AtlasApple::get_app(node);
        std::vector<std::string>  vec = AtlasConfig::parse(node->getstr(), '|');
        int                       len = node->length;
        int                       i;
        for ( i = 0; i < len; ++i )
            static_cast<Gtk::Label*>(app)[i].set_text(vec[i]);
        return 0;
    }
    ret = ret - 1;

    unsigned int len = node->length;
    std::string bg_color = AtlasConfig::fetch("workspace_background");
    std::string hl_color = AtlasConfig::fetch("workspace_highlight");
    Gdk::RGBA   background(bg_color);
    Gdk::RGBA   highlight(hl_color);

    size_t i;
    for ( i = 0; i < len; ++i ) {
        if ( i == (unsigned int)ret )
            static_cast<Gtk::Label*>(node->app)[i].override_background_color(highlight, Gtk::STATE_FLAG_NORMAL);
        else
            static_cast<Gtk::Label*>(node->app)[i].override_background_color(background, Gtk::STATE_FLAG_NORMAL);
    }

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
int AtlasApple::set_next(void)
{
    if ( head == NULL ) {
        head    = new NameApp();
        current = head;
    }
    else {
        current->next = new NameApp();
        current       = current->next;
    }

    AtlasApple::clear(&current);
    return 0;
}

/* ************************************************************************** */
/* Set the name of the node */
int AtlasApple::set_name(std::string name)
{
    current->name = name;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" function of the node */
int AtlasApple::set_func(AtlasGetFunc getstr)
{
    current->getstr = getstr;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" and "event" functions of the node */
int AtlasApple::set_func(AtlasGetFunc getstr, AtlasEventFunc event)
{
    current->getstr = getstr;
    current->event  = event;
    return 0;
}

/* ************************************************************************** */
/* Set the "get", "event", and "signal" functions of the node */
int AtlasApple::set_func(AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
{
    current->getstr = getstr;
    current->event  = event;
    current->signal = signal;
    return 0;
}

/* ************************************************************************** */
/* Set the type of the node */
int AtlasApple::set_type(void)
{
    current->type = AtlasConfig::fetch(current->name, "type");
    return 0;
}

/* ************************************************************************** */
/* Generalized function to initialize and set the application */
int AtlasApple::set_app(void **app)
{
    std::string type = current->type;
    int         len  = current->length;
    std::string              str = current->getstr();
    std::vector<std::string> vec = AtlasConfig::parse(str, '|');
    if ( type.compare("image") == 0 ) {
        *app = new Gtk::Image[len];
        int i;
        for ( i = 0; i < len; ++i )
            static_cast<Gtk::Image*>(*app)[i].set(vec[i]);
    }
    else if ( type.compare("label") == 0 ) {
        *app = new Gtk::Label[len];
        int i;
        for ( i = 0; i < len; ++i )
            static_cast<Gtk::Label*>(*app)[i].set_text(vec[i]);
    }
    else
        return -1;

    return 0;
}


/* ************************************************************************** */
/* Initialize and set the application */
int AtlasApple::set_app(void)
{
    if ( current->name.empty() )
        return -1;

    void *app;
    AtlasApple::set_app(&app);
    if ( current->event == NULL )
        current->app = app;
    else {
        current->app = new Gtk::EventBox();
        static_cast<Gtk::Container*>(current->app)->add(*static_cast<Gtk::Widget*>(app));

        std::string event = AtlasConfig::fetch(current->name, "event");
        if ( event.compare("hover") == 0 )
            static_cast<Gtk::EventBox*>(current->app)->signal_enter_notify_event().connect(sigc::ptr_fun(current->event));
    }

    return 0;
}

/* ************************************************************************** */
/* Set the application alignment */
int AtlasApple::set_align(void)
{
    std::string align = AtlasConfig::fetch(current->name, "align");
    if ( align.empty() )
        return -1;

    if ( align.compare("left") == 0 )
        current->align = AtlasAlign::LEFT;
    else if ( (align.compare("center") == 0) || align.compare("middle") == 0 )
        current->align = AtlasAlign::CENTER;
    else if ( align.compare("right") == 0 )
        current->align = AtlasAlign::RIGHT;
    else
        current->align = AtlasAlign::RIGHT;
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasApple::set_length(void)
{
    unsigned int length = AtlasConfig::fetch_int(current->name, "length");
    if ( length == 0 )
        ++length;
    current->length = length;
    return 0;
}

/* ************************************************************************** */
/* Set the application to update/refresh every given number of seconds */
int AtlasApple::set_update(void)
{
    int time = AtlasConfig::fetch_int(current->name, "update");
    if ( time <= 0 )
        return -1;

    sigc::slot<bool, NameApp*> slot = sigc::ptr_fun((bool (*)(NameApp*))update);
    Glib::signal_timeout().connect_seconds(sigc::bind<NameApp*>(slot, current), time);
    return 0;
}

/* ************************************************************************** */
/* Set the application x-y margins */
int AtlasApple::set_margin(void)
{
    std::string margin = AtlasConfig::fetch(current->name, "margin");
    if ( margin.empty() )
        return -1;

    int          xmargin = atoi(AtlasConfig::cut(margin, 1, ',').c_str());
    int          ymargin = atoi(AtlasConfig::cut(margin, 2, ',').c_str());
    Gtk::Widget *app     = static_cast<Gtk::Widget*>(current->app);
    if ( current->event != NULL )
        app = static_cast<Gtk::EventBox*>(current->app)->get_child();

    AtlasApple::set_margin(*app, xmargin, ymargin);
    return 0;
}

/* ************************************************************************** */
/* Set the application x-y padding */
int AtlasApple::set_padding(void)
{
    std::string padding = AtlasConfig::fetch(current->name, "padding");
    if ( padding.empty() )
        return -1;

    int        xpadding = atoi(AtlasConfig::cut(padding, 1, ',').c_str());
    int        ypadding = atoi(AtlasConfig::cut(padding, 2, ',').c_str());
    Gtk::Misc *app      = static_cast<Gtk::Misc*>(current->app);
    if ( current->event != NULL )
        app = static_cast<Gtk::Misc*>(static_cast<Gtk::EventBox*>(current->app)->get_child());

    AtlasApple::set_padding(*app, xpadding, ypadding);
    return 0;
}

/* ************************************************************************** */
/* Set the application background */
int AtlasApple::set_background(void)
{
    std::string background = AtlasConfig::fetch(current->name, "background");
    if ( background.empty() )
        return -1;

    Gtk::Widget *app = static_cast<Gtk::Widget*>(current->app);
    if ( current->event != NULL )
        app = static_cast<Gtk::EventBox*>(current->app)->get_child();

    AtlasApple::set_background(*app, background);
    return 0;
}

/* ************************************************************************** */
/* Set the application foreground */
int AtlasApple::set_foreground(void)
{
    std::string foreground = AtlasConfig::fetch(current->name, "foreground");
    if ( foreground.empty() )
        return -1;

    Gtk::Widget *app = static_cast<Gtk::Widget*>(current->app);
    if ( current->event != NULL )
        app = static_cast<Gtk::EventBox*>(current->app)->get_child();

    AtlasApple::set_foreground(*app, foreground);
    return 0;
}

/* ************************************************************************** */
/* Set the application font */
int AtlasApple::set_font(void)
{
    std::string font = AtlasConfig::fetch(current->name,     "font");
    int         size = AtlasConfig::fetch_int(current->name, "font-size");
    if ( font.empty() && (size <= 0) )
        return -1;

    Gtk::Widget *app = static_cast<Gtk::Widget*>(current->app);
    if ( current->event != NULL )
        app = static_cast<Gtk::EventBox*>(current->app)->get_child();

    AtlasApple::set_font(*app, font, size);
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
