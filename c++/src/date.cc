/* *****************************************************************************
 * 
 * Name:    date.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: A date application for Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "date.h"
#include "atlas.h"

/* Private functions */
static bool        setdatelabel(void);
static std::string getdatelabel(void);

/* Globals */
static Gtk::Label *widget = NULL;

/* ************************************************************************** */
/* Create date application */
AtlasApp & date(void)
{
    widget = new Gtk::Label(getdatelabel());
    atlas::app::set_margin(*widget, 5, 0);
    atlas::app::set_font(*widget, "GohuFont", 9);

    Glib::signal_timeout().connect_seconds(sigc::ptr_fun(setdatelabel), 1);

    static AtlasApp app(widget, atlas::align::CENTER);
    return app;
}

/* ************************************************************************** */
/* Set date label */
bool setdatelabel(void)
{
    widget->set_label(getdatelabel());
    return true;
}

/* ************************************************************************** */
/* Return date icon path */
std::string getdatelabel(void)
{
    std::string fmt  = "%a %b %-d, %-I:%M:%S %p";
    time_t      t    = time(NULL);
    struct tm*  now  = localtime(&t);
    static char str[30];

    strftime(str, sizeof(str), fmt.c_str(), now);
    return std::string(str);
}
