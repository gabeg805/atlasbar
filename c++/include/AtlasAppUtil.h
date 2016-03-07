/* *****************************************************************************
 * 
 * Name:      AtlasAppUtil.h
 * Namespace: <AtlasAppUtil>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: The Atlas application utility. Contains all non-member functions
 *              that will act on an Atlas Application.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_APP_UTIL_H
#define ATLAS_APP_UTIL_H

/* Includes */
#include "AtlasAppLib.h"
#include <gtkmm.h>
#include <string>

/* Namespace */
namespace AtlasAppUtil
{
    int new_app(NameApp **app);

    int set_name(NameApp *app, std::string name);
    int set_func(NameApp *app, AtlasGetFunc getstr);
    int set_func(NameApp *app, AtlasGetFunc getstr, AtlasEventFunc event);
    int set_func(NameApp *app, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal);
    int set_type(NameApp *app);
    int set_align(NameApp *app);
    int set_length(NameApp *app);
    int set_focus(NameApp *app);
    int set_focus(NameApp *app, int index);
    int set_update(NameApp *app);
    int clear(NameApp *app);

    int init_widget(NameApp *app, void **widget);
    Gtk::Widget * get_widget(NameApp *app);
    int set_widget(NameApp *app);
    int set_widget(NameApp *app, void **widget);
    int set_image(NameApp *app, void **widget);
    int set_label(NameApp *app, void **widget);
    int set_label(NameApp *app);

    int set_focuser(Gtk::Widget &widget, int index, int focus, std::string color);

    int set_background(Gtk::Widget &app, std::string background);
    int set_foreground(Gtk::Widget &app, std::string foreground);
    int set_margin(Gtk::Widget &app, std::string margin);
    int set_margin(Gtk::Widget &app, int margin);
    int set_margin(Gtk::Widget &app, int xmargin, int ymargin);
    int set_padding(Gtk::Misc &app, std::string padding);
    int set_padding(Gtk::Misc &app, int padding);
    int set_padding(Gtk::Misc &app, int xpadding, int ypadding);
    int set_font(Gtk::Widget &app, std::string font);
    int set_font(Gtk::Widget &app, std::string font, int size);
    int set_orientation(Gtk::Orientable &app, std::string orientation);
    int set_size(Gtk::Window &app, int width, int height);
};

#endif /* ATLAS_APP_UTIL_H */
