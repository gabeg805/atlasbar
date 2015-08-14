/* *****************************************************************************
 * 
 * Name:    Workspace.cc
 * Class:   <Workspace>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: A workspace indicator for Atlas. Each workspace is given a name
 *              (via the config file), and the current workspace is highlighted.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "Workspace.h"
#include "AtlasApp.h"
#include "AtlasConfig.h"
#include "AtlasAppSettings.h"
#include <gtkmm.h>
#include <pangomm/fontdescription.h>
#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>

/* Declares */
uint8_t Workspace::screen = 0;

/* *******************************
 * ***** DISPLAY TAGS WIDGET *****
 * *******************************
 */

void Workspace::create(void)
{
    std::vector<std::string> tags      = get_tags();
    uint8_t                  size      = get_tag_size();
    std::string              font      = AtlasConfig::fetch("workspace_font");
    int                      font_size = AtlasConfig::fetch_int("workspace_font_size");
    Gtk::Label              *label     = Gtk::manage(new Gtk::Label[size]);
    size_t i;

    for ( i = 0; i < size; ++i ) {
        label[i].set_text(tags[i]);
        set_font(label[i], font, font_size);
        set_padding(label[i], 5, 0);
    }

    init(label, size, update);
    update(this->widget, 0);
}

/* ****************************
 * ***** SCREEN TAG INDEX *****
 * ****************************
 */

bool Workspace::update(void *w)
{
    update(static_cast<Gtk::Label*>(w), screen);
    return true;
}

void Workspace::update(Gtk::Label *w, uint8_t workspace)
{
    static uint8_t     size     = get_tag_size();
    static std::string bg_color = AtlasConfig::fetch("workspace_background");
    static std::string hl_color = AtlasConfig::fetch("workspace_highlight");
    static Gdk::RGBA   background(bg_color);
    static Gdk::RGBA   highlight(hl_color);
    size_t i;

    for ( i = 0; i < size; ++i ) {
        if ( i == workspace )
            w[i].override_background_color(highlight, Gtk::STATE_FLAG_NORMAL);
        else
            w[i].override_background_color(background, Gtk::STATE_FLAG_NORMAL);
    }

    screen = workspace;
    std::cout << "Workspace: " << int(screen) << std::endl;
}

/* ***********************
 * ***** SCREEN TAGS *****
 * ***********************
 */

std::vector<std::string> Workspace::get_tags(void)
{
    static std::vector<std::string> tags = AtlasConfig::parse(AtlasConfig::FILE, "workspace_tags", ',');
    return tags;
}

uint8_t Workspace::get_tag_size(void)
{
    static size_t size = get_tags().size();
    return size;
}
