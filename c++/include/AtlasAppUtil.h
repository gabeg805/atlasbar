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
#include "atlas.h"
#include "atlastypes.h"
#include "atlasfunc.h"
#include <gtkmm.h>
#include <stdint.h>
#include <string>

/* Namespace */
namespace atlas
{
    namespace app
    {
        namespace util
        {
            int           new_app(atlas::app_t **app);
            int           set_widget(atlas::app_t *app);
            int           set_widget_info(atlas::app_t *app);
            int           set_widget_event(atlas::app_t *app);
            Gtk::Widget * get_widget(atlas::app_t *app);
            Gtk::Widget * get_widget(void *widget, std::string type);
            int           set_image(atlas::app_t *app);
            int           set_label(atlas::app_t *app);

            int           set_name(atlas::app_t *app, std::string name);
            int           set_func(atlas::app_t *app, atlas::func_t *func);
            int           set_signal(atlas::app_t *app, uint32_t signal);
            int           set_type(atlas::app_t *app);
            int           set_align(atlas::app_t *app);
            int           set_length(atlas::app_t *app);
            int           set_focus(atlas::app_t *app);
            int           set_focus(atlas::app_t *app, int index);
            int           set_update(atlas::app_t *app);
            int           clear(atlas::app_t *app);

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
    };
};

#endif /* ATLAS_APP_UTIL_H */
