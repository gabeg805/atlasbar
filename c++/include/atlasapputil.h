/* *****************************************************************************
 * 
 * Name:      atlasapputil.h
 * Namespace: <atlas::app>
 * Author:    Gabriel Gonzalez
 * Email:     gabeg@bu.edu
 * License:   The MIT License (MIT)
 * 
 * Description: The Atlas utility tool for setting widget attributes.
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
#include <gtkmm.h>
#include <string>

/* Namespace */
namespace atlas
{
    namespace app
    {
        int set_background(Gtk::Widget &app, std::string background);
        int set_foreground(Gtk::Widget &app, std::string foreground);
        int set_margin(Gtk::Widget &app, int xmargin, int ymargin);
        int set_padding(Gtk::Misc &app, int xpadding, int ypadding);
        int set_font(Gtk::Widget &app, std::string font);
        int set_font(Gtk::Widget &app, std::string font, int size);
        int set_orientation(Gtk::Orientable &app, std::string orientation);
        int set_size(Gtk::Window &app, int width, int height);
    };
};

#endif /* ATLAS_APP_UTIL_H */
