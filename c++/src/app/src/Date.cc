/* *****************************************************************************
 * 
 * Name:    Date.cc
 * Class:   <Date>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas date application. Displays the date and time.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "Date.h"
#include "AtlasApp.h"
#include "AtlasConfig.h"
#include "AtlasAppSettings.h"
#include <gtkmm.h>
#include <cstdlib>
#include <ctime>
#include <string>

/* ************************************************************************** */
/* Create the application */
void Date::create(void)
{
    Gtk::Label *label = new Gtk::Label(get_time());
    std::string font  = AtlasConfig::fetch("date_font");
    int         size  = AtlasConfig::fetch_int("date_font_size");
    set_margin(*label, 5, 0);
    set_font(*label, font, size);
    init(label);
    connect_callback(update, 1);
}

/* ************************************************************************** */
/* Callback function to periodically update the application text */
bool Date::update(void *w)
{
    static_cast<Gtk::Label*>(w)->set_text(get_time());
    return true;
}

/* ************************************************************************** */
/* Return the text to be used */
std::string Date::get_time(void)
{
    static char        str[30];
    static std::string fmt  = AtlasConfig::fetch("date_fmt");
    time_t             t    = time(NULL);
    struct tm*         now  = localtime(&t);

    strftime(str, sizeof(str), fmt.c_str(), now);

    return std::string(str);
}
