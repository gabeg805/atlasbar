#include "AtlasAppGeneric.h"
#include "AtlasApple.h"
#include "AtlasConfig.h"
#include "AtlasEvent.h"
#include <gtkmm.h>
#include <cstdlib>
#include <string>

/* ************************************************************************** */
/* Set the name of the node */
int AtlasAppGeneric::set_name(NameApp *app, std::string name)
{
    if ( app == NULL )
        return -1;
    app->name = name;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" function of the node */
int AtlasAppGeneric::set_func(NameApp *app, AtlasGetFunc getstr)
{
    if ( app == NULL )
        return -1;
    app->getstr = getstr;
    return 0;
}

/* ************************************************************************** */
/* Set the "get" and "event" functions of the node */
int AtlasAppGeneric::set_func(NameApp *app, AtlasGetFunc getstr, AtlasEventFunc event)
{
    if ( app == NULL )
        return -1;
    app->getstr = getstr;
    app->event  = event;
    return 0;
}

/* ************************************************************************** */
/* Set the "get", "event", and "signal" functions of the node */
int AtlasAppGeneric::set_func(NameApp *app, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal)
{
    if ( app == NULL )
        return -1;
    app->getstr = getstr;
    app->event  = event;
    app->signal = signal;
    return 0;
}

/* ************************************************************************** */
/* Set the type of the node */
int AtlasAppGeneric::set_type(NameApp *app)
{
    if ( app == NULL )
        return -1;
    app->type = AtlasConfig::fetch(app->name, "type");
    return 0;
}

/* ************************************************************************** */
/* Set the application alignment */
int AtlasAppGeneric::set_align(NameApp *app)
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
/* Set the number of sub-applications, within the application */
int AtlasAppGeneric::set_length(NameApp *app)
{
    if ( app == NULL )
        return -1;
    unsigned int length = AtlasConfig::fetch_int(app->name, "length");
    if ( length == 0 )
        ++length;
    app->length = length;
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasAppGeneric::set_focus(NameApp *app)
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
/* Set the application to update/refresh every given number of seconds */
int AtlasAppGeneric::set_update(NameApp *app)
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
/* Clear the node structure */
int AtlasAppGeneric::clear(NameApp *app)
{
    if ( app == NULL )
        return -1;
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

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

/* ************************************************************************** */
/* Set the background color of an application  */
int AtlasAppGeneric::set_background(Gtk::Widget &app, std::string background)
{
    if ( background.empty() )
        return -1;

    Gdk::RGBA color(background);
    app.override_background_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the foreground color of an application */
int AtlasAppGeneric::set_foreground(Gtk::Widget &app, std::string foreground)
{
    if ( foreground.empty() )
        return -1;

    Gdk::RGBA color(foreground);
    app.override_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the margin size for an application */
int AtlasAppGeneric::set_margin(Gtk::Widget &app, std::string margin)
{
    int xmargin = atoi(AtlasConfig::cut(margin, 1, ',').c_str());
    int ymargin = atoi(AtlasConfig::cut(margin, 2, ',').c_str());
    AtlasAppGeneric::set_margin(app, xmargin, ymargin);
    return 0;
}

/* ************************************************************************** */
/* Set the margin size for an application */
int AtlasAppGeneric::set_margin(Gtk::Widget &app, int margin)
{
    AtlasAppGeneric::set_margin(app, margin, margin);
    return 0;
}

/* ************************************************************************** */
/* Set the margin size for an application */
int AtlasAppGeneric::set_margin(Gtk::Widget &app, int xmargin, int ymargin)
{
    app.set_margin_start(xmargin);
    app.set_margin_end(xmargin);
    app.set_margin_top(ymargin);
    app.set_margin_bottom(ymargin);
    return 0;
}

/* ************************************************************************** */
/* Set the padding size for an application */
int AtlasAppGeneric::set_padding(Gtk::Misc &app, std::string padding)
{
    int xpadding = atoi(AtlasConfig::cut(padding, 1, ',').c_str());
    int ypadding = atoi(AtlasConfig::cut(padding, 2, ',').c_str());
    AtlasAppGeneric::set_padding(app, xpadding, ypadding);
    return 0;
}

/* ************************************************************************** */
/* Set the padding size for an application */
int AtlasAppGeneric::set_padding(Gtk::Misc &app, int padding)
{
    AtlasAppGeneric::set_padding(app, padding, padding);
    return 0;
}

/* ************************************************************************** */
/* Set the padding size for an application */
int AtlasAppGeneric::set_padding(Gtk::Misc &app, int xpadding, int ypadding)
{
    app.set_padding(xpadding, ypadding);
    return 0;
}

/* ************************************************************************** */
/* Set the font of an application */
int AtlasAppGeneric::set_font(Gtk::Widget &app, std::string font)
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
int AtlasAppGeneric::set_font(Gtk::Widget &app, std::string font, int size)
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
int AtlasAppGeneric::set_orientation(Gtk::Orientable &app, std::string orientation)
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
int AtlasAppGeneric::set_size(Gtk::Window &app, int width, int height)
{
    app.set_default_size(width, height);
    return 0;
}











// /* ************************************************************************** */
// /* Update applications */
// bool AtlasApple::update(NameApp *node)
// {
//     return AtlasApple::update(node, 0);
// }        

// /* ************************************************************************** */
// /* Update applications */
// bool AtlasApple::update(NameApp *node, int ret)
// {
//     if ( node == NULL )
//         return false;

//     std::string type = node->type;
//     if ( type.compare("image") == 0 )
//         AtlasApple::doimage(node, ret);
//     else if ( type.compare("label") == 0 )
//         AtlasApple::dolabel(node, ret);
//     else
//         ;

//     return true;
// }

// int AtlasApple::doimage(NameApp *node, int ret)
// {
//     if ( ret == 0 ) {
//         Gtk::Widget              *app = AtlasApple::get_app(node);
//         std::vector<std::string>  vec = AtlasConfig::parse(node->getstr(), '|');
//         int                       len = node->length;
//         int                       i;
//         for ( i = 0; i < len; ++i )
//             static_cast<Gtk::Image*>(app)[i].set(vec[i]);
//         return 0;
//     }

//     return 0;
// }

// int AtlasApple::dolabel(NameApp *node, int ret)
// {
//     std::cout << "doing label: " << node->name << std::endl;
//     std::cout << "setting focus: " << ret << std::endl;
//     AtlasApple::set_focus(node, ret);
//     AtlasApple::set_label(node);
//     std::cout << "Workspace: " << ret << std::endl;

//     return 0;
// }

// /* ************************************************************************** */
// /* Initialize and set an image application */
// int AtlasApple::set_image(NameApp *node, void **app)
// {
//     Gtk::Image               *img    = static_cast<Gtk::Image*>(*app);
//     std::vector<std::string>  strvec = AtlasConfig::parse(node->getstr(), '|');
//     std::string               name   = node->name;
//     int                       len    = node->length;
//     int i;
//     for ( i = 0; i < len; ++i ) {
//         img[i].set(strvec[i]);
//         set_margin(name, img[i]);
//         set_padding(name, img[i]);
//         set_background(name, img[i]);
//         set_foreground(name, img[i]);
//     }

//     return 0;
// }

// /* ************************************************************************** */
// /* Initialize and set a label application */
// int AtlasApple::set_label(NameApp *node)
// {
//     void *app = AtlasApple::get_app(node);
//     return AtlasApple::set_label(node, &app);
// }

// int AtlasApple::set_focuser(Gtk::Widget &app, int index, int focus, std::string color)
// {
//     if ( focus < 0 )
//         return -1;
//     else {
//         if ( index == focus )
//             set_foreground(app, color);
//         else
//             return -1;
//     }
//     return 0;
// }

// /* ************************************************************************** */
// /* Initialize and set a label application */
// int AtlasApple::set_label(NameApp *node, void **app)
// {
//     Gtk::Label               *label      = static_cast<Gtk::Label*>(*app);
//     std::string               name       = node->name;
//     std::vector<std::string>  strvec     = AtlasConfig::parse(node->getstr(), '|');
//     std::string               font       = AtlasConfig::fetch(name, "font");
//     int                       size       = AtlasConfig::fetch_int(name, "font-size");
//     int                       margin     = AtlasConfig::fetch_int(name, "margin");
//     int                       padding    = AtlasConfig::fetch_int(name, "padding");
//     std::string               background = AtlasConfig::fetch(name, "background");
//     std::string               foreground = AtlasConfig::fetch(name, "foreground");
//     std::string               focus_color = AtlasConfig::fetch(name, "focus-color");
//     int                       focus      = node->focus;
//     int                       len        = node->length;
//     int i;
//     for ( i = 0; i < len; ++i ) {
//         label[i].set_text(strvec[i]);
//         set_font(label[i], font, size);
//         set_margin(label[i], margin, margin);
//         set_padding(label[i], padding, padding);
//         set_background(label[i], background);
//         set_foreground(label[i], foreground);
//         set_focuser(label[i], i, focus, focus_color);
//     }

//     return 0;
// }

// /* ************************************************************************** */
// /* Generalized function to initialize and set the application */
// int AtlasApple::set_app(NameApp *node, void **app)
// {
//     std::string type = node->type;
//     if ( type.compare("image") == 0 )
//         AtlasApple::set_image(node, app);
//     else if ( type.compare("label") == 0 )
//         AtlasApple::set_label(node, app);
//     else
//         return -1;

//     return 0;
// }
