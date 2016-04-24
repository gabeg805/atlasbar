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
#include "atlasconf.h"
#include "atlasevent.h"
#include "atlasio.h"
#include <gtkmm.h>
#include <cstdlib>
#include <string>

/* ************************************************************************** */
/* Allocate space for a new application */
int AtlasAppUtil::new_app(atlas::app **app)
{
    *app = new atlas::app();
    AtlasAppUtil::clear(*app);
    return 0;
}

/* ************************************************************************** */
/* Initialize and set the application */
int AtlasAppUtil::set_widget(atlas::app *app)
{
    if ( (app == NULL) || app->name.empty() )
        return -1;


    std::string type = app->type;
    int         len  = app->length;
    if ( type.compare("image") == 0 )
        app->widget = new Gtk::Image[len];
    else if ( type.compare("label") == 0 )
        app->widget = new Gtk::Label[len];
    else
        return -1;

    AtlasAppUtil::set_widget_event(app);
    AtlasAppUtil::set_widget_info(app);
    return 0;
}

/* ************************************************************************** */
/* Set the widget information */
int AtlasAppUtil::set_widget_info(atlas::app *app)
{
    if ( app == NULL )
        return -1;

    std::string type = app->type;
    if ( type.compare("image") == 0 )
        AtlasAppUtil::set_image(app);
    else if ( type.compare("label") == 0 )
        AtlasAppUtil::set_label(app);
    else
        return -1;
    return 0;
}

/* ************************************************************************** */
/* Set the widget event */
int AtlasAppUtil::set_widget_event(atlas::app *app)
{
    std::string event = atlasconf::find(app->name, "event");
    if ( event.empty() || (app->func->event == NULL) )
        return -1;

    /* Add widget to app */
    Gtk::Widget *widget = static_cast<Gtk::Widget*>(app->widget);
    app->widget         = new Gtk::EventBox();
    static_cast<Gtk::Container*>(app->widget)->add(*widget);

    /* Set signal events for widget */
    sigc::pointer_functor1<void*, int>  func = sigc::ptr_fun(app->func->event);
    Gtk::EventBox                      *box  = static_cast<Gtk::EventBox*>(app->widget);
    if ( event.compare("hover") == 0 )
        box->signal_enter_notify_event().connect(func);
    else if ( event.compare("click") == 0 )
        box->signal_button_release_event().connect(func);
    else
        return -1;
    return 0;
}

/* ************************************************************************** */
/* Return the application's widget */
Gtk::Widget * AtlasAppUtil::get_widget(atlas::app *app)
{
    if ( app == NULL )
        return NULL;

    std::string  event  = atlasconf::find(app->name, "event");
    if ( event.empty() )
        return static_cast<Gtk::Widget*>(app->widget);
    else
        return static_cast<Gtk::EventBox*>(app->widget)->get_child();
}

/* ************************************************************************** */
/* Return the application's widget */
Gtk::Widget * AtlasAppUtil::get_widget(void *widget, std::string type)
{
    if ( widget == NULL )
        return NULL;

    if ( type.compare("label") == 0 )
        return static_cast<Gtk::Label*>(widget);
    else if ( type.compare("image") == 0 )
        return static_cast<Gtk::Image*>(widget);
    else
        return static_cast<Gtk::Widget*>(widget);
}

/* ************************************************************************** */
/* Set the applications image widget */
int AtlasAppUtil::set_image(atlas::app *app)
{
    if ( app == NULL )
        return -1;

    Gtk::Widget              *widget     = AtlasAppUtil::get_widget(app);
    Gtk::Image               *image      = static_cast<Gtk::Image*>(widget);
    std::vector<std::string>  split      = atlasio::split(app->func->info(), '|');
    std::string               name       = app->name;
    std::string               margin     = atlasconf::find(name, "margin");
    std::string               padding    = atlasconf::find(name, "padding");
    std::string               background = atlasconf::find(name, "background");
    std::string               foreground = atlasconf::find(name, "foreground");
    int                       len        = app->length;
    int i;
    for ( i = 0; i < len; ++i ) {
        image[i].set(split[i]);
        AtlasAppUtil::set_margin(image[i], margin);
        AtlasAppUtil::set_padding(image[i], padding);
        AtlasAppUtil::set_background(image[i], background);
        AtlasAppUtil::set_foreground(image[i], foreground);
    }

    return 0;
}

/* ************************************************************************** */
/* Set the application's label widget */
int AtlasAppUtil::set_label(atlas::app *app)
{
    Gtk::Widget              *widget      = AtlasAppUtil::get_widget(app);
    Gtk::Label               *label       = static_cast<Gtk::Label*>(widget);
    std::string               name        = app->name;
    std::vector<std::string>  split       = atlasio::split(app->func->info(), '|');
    std::string               margin      = atlasconf::find(name, "margin");
    std::string               padding     = atlasconf::find(name, "padding");
    std::string               background  = atlasconf::find(name, "background");
    std::string               foreground  = atlasconf::find(name, "foreground");
    std::string               focus_color = atlasconf::find(name, "focus-color");
    std::string               font        = atlasconf::find(name, "font");
    int                       size        = atlasconf::find_int(name, "font-size");
    int                       focus       = app->focus;
    int                       len         = app->length;
    int i;
    for ( i = 0; i < len; ++i ) {
        label[i].set_text(split[i]);
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
int AtlasAppUtil::set_name(atlas::app *app, std::string name)
{
    if ( app == NULL )
        return -1;
    app->name = name;
    return 0;
}

/* ************************************************************************** */
/* Set the "get", "event", and "signal" functions of the application */
int AtlasAppUtil::set_func(atlas::app *app, AtlasFunc *func)
{
    if ( app == NULL )
        return -1;
    app->func = func;
    return 0;
}

/* ************************************************************************** */
/* Set the type of the application */
int AtlasAppUtil::set_type(atlas::app *app)
{
    if ( app == NULL )
        return -1;
    app->type = atlasconf::find(app->name, "type");
    return 0;
}

/* ************************************************************************** */
/* Set the application alignment */
int AtlasAppUtil::set_align(atlas::app *app)
{
    if ( app == NULL )
        return -1;

    std::string align = atlasconf::find(app->name, "align");
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
int AtlasAppUtil::set_length(atlas::app *app)
{
    if ( app == NULL )
        return -1;
    uint8_t length = atlasconf::find_int(app->name, "length");
    if ( length == 0 )
        length = 1;
    app->length = length;
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasAppUtil::set_focus(atlas::app *app)
{
    if ( app == NULL )
        return -1;
    std::string str = atlasconf::find(app->name, "focus");
    if ( str.empty() )
        app->focus = -1;
    else
        app->focus = atoi(str.c_str());
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasAppUtil::set_focus(atlas::app *app, int index)
{
    app->focus = index;
    return 0;
}

/* ************************************************************************** */
/* Set the application to update/refresh every given number of seconds */
int AtlasAppUtil::set_update(atlas::app *app)
{
    if ( app == NULL )
        return -1;

    int time = atlasconf::find_int(app->name, "update");
    if ( time <= 0 )
        return -1;
    sigc::slot<bool, atlas::app*> slot = sigc::ptr_fun((bool (*)(atlas::app*))atlasevent::update);
    Glib::signal_timeout().connect_seconds(sigc::bind<atlas::app*>(slot, app), time);
    return 0;
}

/* ************************************************************************** */
/* Clear the application struct */
int AtlasAppUtil::clear(atlas::app *app)
{
    if ( app == NULL )
        return -1;
    app->name   = "";
    app->type   = "";
    app->align  = AtlasAlign::NONE;
    app->length = 0;
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
    int xmargin = atoi(atlasio::cut(margin, 1, ',').c_str());
    int ymargin = atoi(atlasio::cut(margin, 2, ',').c_str());
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
    int xpadding = atoi(atlasio::cut(padding, 1, ',').c_str());
    int ypadding = atoi(atlasio::cut(padding, 2, ',').c_str());
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
    if ( !atlasconf::find(name, "").empty() )
        return true;
    else {
        atlasio::debug("Application '"+name+"' not found in config file.");
        return false;
    }
}
