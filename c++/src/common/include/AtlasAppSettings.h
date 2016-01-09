/* *****************************************************************************
 * 
 * Name:    AtlasAppSettings.h
 * Class:   None.
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Syntax: #include "AtlasAppSettings.h"
 * 
 * Description: Modify Atlas applications focusing on individual GTK settings.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_APP_SETTINGS_H
#define ATLAS_APP_SETTINGS_H

/* Includes */
#include "AtlasApp.h"
#include <gtkmm.h>
#include <cstddef>
#include <string>
#include <vector>

/* Return program command output */
int set_image(Gtk::Image &w, std::string str);
int set_image(Gtk::Image &w, size_t s, std::vector<std::string> vec);
int set_label(Gtk::Label &w, std::string str);
int set_label(Gtk::Label &w, size_t s, std::vector<std::string> vec);
int set_padding(Gtk::Misc &w, int x, int y);
int set_margin(void *w, int x, int y);
int set_background(Gtk::Widget &w, std::string background);
int set_foreground(Gtk::Widget &w, std::string foreground);
int set_font(Gtk::Widget &w, std::string font);
int set_font(Gtk::Widget &w, std::string font, int size);
int set_orientation(Gtk::Orientable &w, std::string orientation);

#endif /* ATLAS_APP_SETTINGS_H */
