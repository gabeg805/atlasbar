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
#include "AtlasApp.h"
#include "AtlasFunc.h"
#include <gtkmm.h>
#include <string>

/* Namespace */
namespace AtlasAppUtil
{
    int           new_app(atlas::app **app);
    int           set_widget(atlas::app *app);

    int           init_widget(atlas::app *app, void **widget);
    int           set_widget(atlas::app *app, void **widget);
    int           set_event_widget(atlas::app *app, void **widget);

    Gtk::Widget * get_widget(atlas::app *app);
    int           set_image(atlas::app *app, void **widget);
    int           set_label(atlas::app *app, void **widget);
    int           set_label(atlas::app *app);

    int           set_name(atlas::app *app, std::string name);
    // int           set_func(atlas::app *app, AtlasGetFunc getstr);
    // int           set_func(atlas::app *app, AtlasGetFunc getstr, AtlasEventFunc event);
    // int           set_func(atlas::app *app, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal);
    int           set_func(atlas::app *app, AtlasFunc *func);
    int           set_type(atlas::app *app);
    int           set_align(atlas::app *app);
    int           set_length(atlas::app *app);
    int           set_focus(atlas::app *app);
    int           set_focus(atlas::app *app, int index);
    int           set_update(atlas::app *app);
    int           clear(atlas::app *app);

    int           set_focuser(Gtk::Widget &widget, int index, int focus, std::string color);
    int           set_background(Gtk::Widget &app, std::string background);
    int           set_foreground(Gtk::Widget &app, std::string foreground);
    int           set_margin(Gtk::Widget &app, std::string margin);
    int           set_margin(Gtk::Widget &app, int margin);
    int           set_margin(Gtk::Widget &app, int xmargin, int ymargin);
    int           set_padding(Gtk::Misc &app, std::string padding);
    int           set_padding(Gtk::Misc &app, int padding);
    int           set_padding(Gtk::Misc &app, int xpadding, int ypadding);
    int           set_font(Gtk::Widget &app, std::string font);
    int           set_font(Gtk::Widget &app, std::string font, int size);
    int           set_orientation(Gtk::Orientable &app, std::string orientation);
    int           set_size(Gtk::Window &app, int width, int height);

    bool          is_app(std::string name);
};

#endif /* ATLAS_APP_UTIL_H */
