/* *****************************************************************************
 * 
 * Name:      atlasapputil.cc
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

/* Includes */
#include "atlasapputil.h"
#include <gtkmm.h>
#include <string>

/* ************************************************************************** */
/* Set background color of widget  */
int atlas::app::set_background(Gtk::Widget &widget, std::string background)
{
    if ( background.empty() )
        return -1;
    Gdk::RGBA color(background);
    widget.override_background_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set foreground color of widget */
int atlas::app::set_foreground(Gtk::Widget &widget, std::string foreground)
{
    if ( foreground.empty() )
        return -1;
    Gdk::RGBA color(foreground);
    widget.override_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set margin for widget */
int atlas::app::set_margin(Gtk::Widget &widget, int xmargin, int ymargin)
{
    widget.set_margin_start(xmargin);
    widget.set_margin_end(xmargin);
    widget.set_margin_top(ymargin);
    widget.set_margin_bottom(ymargin);
    return 0;
}

/* ************************************************************************** */
/* Set padding for widget */
int atlas::app::set_padding(Gtk::Misc &widget, int xpadding, int ypadding)
{
    widget.set_padding(xpadding, ypadding);
    return 0;
}

/* ************************************************************************** */
/* Set widget font */
int atlas::app::set_font(Gtk::Widget &widget, std::string font)
{
    if ( font.empty() )
        return -1;
    Pango::FontDescription fd;
    fd.set_family(font);
    widget.override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Set widget font and text size */
int atlas::app::set_font(Gtk::Widget &widget, std::string font, int size)
{
    if ( font.empty() || (size <= 0) )
        return -1;
    Pango::FontDescription fd;
    fd.set_family(font);
    fd.set_size(size * PANGO_SCALE);
    widget.override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Set widget orientation */
int atlas::app::set_orientation(Gtk::Orientable &widget,
                                      std::string orientation)
{
    if ( orientation.compare("vertical") == 0 )
        widget.set_orientation(Gtk::ORIENTATION_VERTICAL);
    else if ( orientation.compare("horizontal") == 0 )
        widget.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    else
        return -1;
    return 0;
}

/* ************************************************************************** */
/* Set widget size */
int atlas::app::set_size(Gtk::Window &widget, int width, int height)
{
    widget.set_default_size(width, height);
    return 0;
}
