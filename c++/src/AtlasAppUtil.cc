/* *****************************************************************************
 * 
 * Name:    AtlasAppUtil.cc
 * Class:   <AtlasAppUtil>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Application utility for setting Atlas Application
 *              attributes.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasAppUtil.h"
#include "AtlasApp.h"
#include "AtlasConfig.h"
#include "AtlasEvent.h"
#include "atlasio.h"
#include <gtkmm.h>
#include <cstdlib>
#include <string>

/* ************************************************************************** */
/* Allocate space for a new application */
int AtlasAppUtil::new_app(NameApp **app)
{
    *app = new NameApp();
    AtlasAppUtil::clear(*app);
    return 0;
}

/* ************************************************************************** */
/* Initialize and set the application */
int AtlasAppUtil::set_widget(NameApp *app)
{
    if ( app == NULL )
        return -1;

    std::string name = app->name;
    if ( name.empty() )
        return -1;

    void *widget;
    AtlasAppUtil::init_widget(app, &widget);
    AtlasAppUtil::set_widget(app, &widget);
    AtlasAppUtil::set_event_widget(app, &widget);

    return 0;
}

/* ************************************************************************** */
/* Initialize and set one or more widgets */
int AtlasAppUtil::init_widget(NameApp *app, void **widget)
{
    if ( app == NULL )
        return -1;

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
/* Generalized function to initialize and set the application */
int AtlasAppUtil::set_widget(NameApp *app, void **widget)
{
    if ( app == NULL )
        return -1;

    std::string  type = app->type;
    if ( type.compare("image") == 0 )
        AtlasAppUtil::set_image(app, widget);
    else if ( type.compare("label") == 0 )
        AtlasAppUtil::set_label(app, widget);
    else
        return -1;

    app->widget = *widget;
    return 0;
}

/* ************************************************************************** */
/* Set the application widget as an event widget */
int AtlasAppUtil::set_event_widget(NameApp *app, void **widget)
{
    if ( app->func->event == NULL )
        return -1;

    app->widget = new Gtk::EventBox();
    static_cast<Gtk::Container*>(app->widget)->add(*static_cast<Gtk::Widget*>(*widget));

    std::string event = AtlasConfig::fetch(app->name, "event");
    if ( event.compare("hover") == 0 )
        static_cast<Gtk::EventBox*>(app->widget)->signal_enter_notify_event().connect(sigc::ptr_fun(app->func->event));

    return 0;
}

/* ************************************************************************** */
/* Return the application's widget */
Gtk::Widget * AtlasAppUtil::get_widget(NameApp *app)
{
    if ( app == NULL )
        return NULL;

    void        *widget = app->widget;
    std::string  name   = app->name;
    std::string  event  = AtlasConfig::fetch(name, "event");
    if ( event.empty() )
        return static_cast<Gtk::Widget*>(widget);
    else
        return static_cast<Gtk::EventBox*>(widget)->get_child();
}

/* ************************************************************************** */
/* Set the applications image widget */
int AtlasAppUtil::set_image(NameApp *app, void **widget)
{
    if ( app == NULL )
        return -1;

    Gtk::Image               *image      = static_cast<Gtk::Image*>(*widget);
    // std::vector<std::string>  strvec     = AtlasConfig::parse(app->getstr(), '|');
    std::vector<std::string>  strvec     = AtlasConfig::parse(app->func->info(), '|');
    std::string               name       = app->name;
    int                       len        = app->length;
    std::string               margin     = AtlasConfig::fetch(name, "margin");
    std::string               padding    = AtlasConfig::fetch(name, "padding");
    std::string               background = AtlasConfig::fetch(name, "background");
    std::string               foreground = AtlasConfig::fetch(name, "foreground");
    int i;
    for ( i = 0; i < len; ++i ) {
        image[i].set(strvec[i]);
        AtlasAppUtil::set_margin(image[i], margin);
        AtlasAppUtil::set_padding(image[i], padding);
        AtlasAppUtil::set_background(image[i], background);
        AtlasAppUtil::set_foreground(image[i], foreground);
    }

    return 0;
}

/* ************************************************************************** */
/* Set the application's label widget */
int AtlasAppUtil::set_label(NameApp *app)
{
    void *widget = AtlasAppUtil::get_widget(app);
    return AtlasAppUtil::set_label(app, &widget);
}

/* ************************************************************************** */
/* Set the application's label widget */
int AtlasAppUtil::set_label(NameApp *app, void **widget)
{
    Gtk::Label               *label       = static_cast<Gtk::Label*>(*widget);
    std::string               name        = app->name;
    int                       len         = app->length;
    int                       focus       = app->focus;
    // std::vector<std::string>  strvec      = AtlasConfig::parse(app->getstr(), '|');
    std::vector<std::string>  strvec      = AtlasConfig::parse(app->func->info(), '|');
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
        AtlasAppUtil::set_font(label[i], font, size);
        AtlasAppUtil::set_margin(label[i], margin);
        AtlasAppUtil::set_padding(label[i], padding);
        AtlasAppUtil::set_background(label[i], background);
        AtlasAppUtil::set_foreground(label[i], foreground);
        AtlasAppUtil::set_focuser(label[i], i, focus, focus_color);
    }

    return 0;
}

/* ************************************************************************** */
/* Set the name of the application */
int AtlasAppUtil::set_name(NameApp *app, std::string name)
{
    if ( app == NULL )
        return -1;
    app->name = name;
    return 0;
}

// /* ************************************************************************** */
// /* Set the "get" function of the application */
// int AtlasAppUtil::set_func(NameApp *app, AtlasGetFunc getstr)
// {
//     if ( app == NULL )
//         return -1;
//     app->getstr = getstr;
//     return 0;
// }

// /* ************************************************************************** */
// /* Set the "get" and "event" functions of the application */
// int AtlasAppUtil::set_func(NameApp *app, AtlasGetFunc getstr, AtlasEventFunc event)
// {
//     if ( app == NULL )
//         return -1;
//     app->getstr = getstr;
//     app->event  = event;
//     return 0;
// }

/* ************************************************************************** */
/* Set the "get", "event", and "signal" functions of the application */
// int AtlasAppUtil::set_func(NameApp *app, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
int AtlasAppUtil::set_func(NameApp *app, AtlasFunc *func)
{
    if ( app == NULL )
        return -1;
    // app->getstr = getstr;
    // app->event  = event;
    // app->signal = signal;
    app->func = func;
    return 0;
}

/* ************************************************************************** */
/* Set the type of the application */
int AtlasAppUtil::set_type(NameApp *app)
{
    if ( app == NULL )
        return -1;
    app->type = AtlasConfig::fetch(app->name, "type");
    return 0;
}

/* ************************************************************************** */
/* Set the application alignment */
int AtlasAppUtil::set_align(NameApp *app)
{
    if ( app == NULL )
        return -1;

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
/* Set the number of widgets within the application */
int AtlasAppUtil::set_length(NameApp *app)
{
    if ( app == NULL )
        return -1;
    uint8_t length = AtlasConfig::fetch_int(app->name, "length");
    if ( length == 0 )
        length = 1;
    app->length = length;
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasAppUtil::set_focus(NameApp *app)
{
    if ( app == NULL )
        return -1;
    std::string str = AtlasConfig::fetch(app->name, "focus");
    if ( str.empty() )
        app->focus = -1;
    else
        app->focus = atoi(str.c_str());
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasAppUtil::set_focus(NameApp *app, int index)
{
    app->focus = index;
    return 0;
}

/* ************************************************************************** */
/* Set the application to update/refresh every given number of seconds */
int AtlasAppUtil::set_update(NameApp *app)
{
    if ( app == NULL )
        return -1;

    int time = AtlasConfig::fetch_int(app->name, "update");
    if ( time <= 0 )
        return -1;
    sigc::slot<bool, NameApp*> slot = sigc::ptr_fun((bool (*)(NameApp*))AtlasEvent::update);
    Glib::signal_timeout().connect_seconds(sigc::bind<NameApp*>(slot, app), time);
    return 0;
}

/* ************************************************************************** */
/* Clear the application struct */
int AtlasAppUtil::clear(NameApp *app)
{
    if ( app == NULL )
        return -1;
    app->name   = "";
    app->type   = "";
    app->align  = AtlasAlign::NONE;
    app->length = 0;
    // app->getstr = NULL;
    // app->event  = NULL;
    // app->signal = NULL;
    app->func   = NULL;
    app->widget = NULL;
    return 0;
}

/* ************************************************************************** */
int AtlasAppUtil::set_focuser(Gtk::Widget &widget, int index, int focus, std::string color)
{
    if ( focus < 0 )
        return -1;
    else {
        if ( index == focus )
            AtlasAppUtil::set_foreground(widget, color);
        else
            return -1;
    }
    return 0;
}

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Set the background color of an application  */
int AtlasAppUtil::set_background(Gtk::Widget &app, std::string background)
{
    if ( background.empty() )
        return -1;

    Gdk::RGBA color(background);
    app.override_background_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the foreground color of an application */
int AtlasAppUtil::set_foreground(Gtk::Widget &app, std::string foreground)
{
    if ( foreground.empty() )
        return -1;

    Gdk::RGBA color(foreground);
    app.override_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the margin size for an application */
int AtlasAppUtil::set_margin(Gtk::Widget &app, std::string margin)
{
    int xmargin = atoi(AtlasConfig::cut(margin, 1, ',').c_str());
    int ymargin = atoi(AtlasConfig::cut(margin, 2, ',').c_str());
    AtlasAppUtil::set_margin(app, xmargin, ymargin);
    return 0;
}

/* ************************************************************************** */
/* Set the margin size for an application */
int AtlasAppUtil::set_margin(Gtk::Widget &app, int margin)
{
    AtlasAppUtil::set_margin(app, margin, margin);
    return 0;
}

/* ************************************************************************** */
/* Set the margin size for an application */
int AtlasAppUtil::set_margin(Gtk::Widget &app, int xmargin, int ymargin)
{
    app.set_margin_start(xmargin);
    app.set_margin_end(xmargin);
    app.set_margin_top(ymargin);
    app.set_margin_bottom(ymargin);
    return 0;
}

/* ************************************************************************** */
/* Set the padding size for an application */
int AtlasAppUtil::set_padding(Gtk::Misc &app, std::string padding)
{
    int xpadding = atoi(AtlasConfig::cut(padding, 1, ',').c_str());
    int ypadding = atoi(AtlasConfig::cut(padding, 2, ',').c_str());
    AtlasAppUtil::set_padding(app, xpadding, ypadding);
    return 0;
}

/* ************************************************************************** */
/* Set the padding size for an application */
int AtlasAppUtil::set_padding(Gtk::Misc &app, int padding)
{
    AtlasAppUtil::set_padding(app, padding, padding);
    return 0;
}

/* ************************************************************************** */
/* Set the padding size for an application */
int AtlasAppUtil::set_padding(Gtk::Misc &app, int xpadding, int ypadding)
{
    app.set_padding(xpadding, ypadding);
    return 0;
}

/* ************************************************************************** */
/* Set the font of an application */
int AtlasAppUtil::set_font(Gtk::Widget &app, std::string font)
{
    if ( font.empty() )
        return -1;

    /* Find this from app */
    Pango::FontDescription fd;
    fd.set_family(font);
    app.override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Set the font and text size of an application */
int AtlasAppUtil::set_font(Gtk::Widget &app, std::string font, int size)
{
    if ( font.empty() || (size <= 0) )
        return -1;

    /* Find this from app */
    Pango::FontDescription fd;
    fd.set_family(font);
    fd.set_size(size * PANGO_SCALE);
    app.override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Set the orientation of an application */
int AtlasAppUtil::set_orientation(Gtk::Orientable &app, std::string orientation)
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
int AtlasAppUtil::set_size(Gtk::Window &app, int width, int height)
{
    app.set_default_size(width, height);
    return 0;
}

/* ************************************************************************** */
/* Check if valid application or not */
bool AtlasAppUtil::is_app(std::string name)
{
    if ( AtlasConfig::exists(name) )
        return true;
    else {
        atlasio::debug("Application '"+name+"' not found in config file.");
        return false;
    }
}
