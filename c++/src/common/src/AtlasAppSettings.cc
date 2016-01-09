/* *****************************************************************************
 * 
 * Name:    AtlasAppSettings.cc
 * Class:   None.
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Syntax: None.
 * 
 * Description: Modify Atlas applications focusing on individual GTK settings.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "AtlasAppSettings.h"
#include "AtlasApp.h"
#include <gtkmm.h>
#include <ctype.h>
#include <pangomm/fontdescription.h>
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <string>
#include <vector>

/* ************************************************************************** */
/* Set the image of an application */
int set_image(Gtk::Image &w, std::string str)
{
    w.set(str);
    return 0;
}

/* ************************************************************************** */
/* Set the images of an application */
int set_image(Gtk::Image &w, size_t s, std::vector<std::string> vec)
{
    std::vector<std::string>::iterator iter;
    size_t i;

    for ( iter = vec.begin(), i = 0;
          (iter != vec.end()) && (i < s);
          ++iter, ++i )
    {
        set_image(w, *iter);
    }
    return 0;
}

/* ************************************************************************** */
/* Set the label of an application */
int set_label(Gtk::Label &w, std::string str)
{
    w.set_label(str);
    return 0;
}

/* ************************************************************************** */
/* Set the labels of an application */
int set_label(Gtk::Label &w, size_t s, std::vector<std::string> vec)
{
    std::vector<std::string>::iterator iter;
    size_t i;

    for ( iter = vec.begin(), i = 0;
          (iter != vec.end()) && (i < s);
          ++iter, ++i )
    {
        set_label(w, *iter);
    }
    return 0;
}

/* ************************************************************************** */
/* Set the application's XY window padding */
int set_padding(Gtk::Misc &w, int x, int y)
{
    w.set_padding(x, y);
    return 0;
}

/* ************************************************************************** */
/* Set the application's XY window margins */
int set_margin(void *w, int x, int y)
{
    static_cast<Gtk::Widget*>(w)->set_margin_start(x);
    static_cast<Gtk::Widget*>(w)->set_margin_end(x);
    static_cast<Gtk::Widget*>(w)->set_margin_top(y);
    static_cast<Gtk::Widget*>(w)->set_margin_bottom(y);
    return 0;
}

/* ************************************************************************** */
/* Set the background color of the application  */
int set_background(Gtk::Widget &w, std::string background)
{
    Gdk::RGBA color(background);
    w.override_background_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set foreground color of the application */
int set_foreground(Gtk::Widget &w, std::string foreground)
{
    Gdk::RGBA color(foreground);
    w.override_color(color, Gtk::STATE_FLAG_NORMAL);
    return 0;
}

/* ************************************************************************** */
/* Set the font of the application */
int set_font(Gtk::Widget &w, std::string font)
{
    Pango::FontDescription fd;
    fd.set_family(font);
    w.override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Set the font and text size of the application */
int set_font(Gtk::Widget &w, std::string font, int size)
{
    Pango::FontDescription fd;
    fd.set_family(font);
    fd.set_size(size * PANGO_SCALE);
    w.override_font(fd);
    return 0;
}

/* ************************************************************************** */
/* Set the orientation of the application */
int set_orientation(Gtk::Orientable &w, std::string orientation)
{
    if ( orientation.compare("vertical") == 0 )
        w.set_orientation(Gtk::ORIENTATION_VERTICAL);
    else if ( orientation.compare("horizontal") == 0 )
        w.set_orientation(Gtk::ORIENTATION_HORIZONTAL);
    else
        return -1;
    return 0;
}
