/* *****************************************************************************
 * 
 * Name:    AtlasApp.h
 * Class:   <AtlasApp>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: Atlas application builder.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header Guard */
#ifndef ATLAS_APP_H
#define ATLAS_APP_H

/* Includes */
#include "AtlasAlignType.h"
#include "AtlasAppSettings.h"
#include <gtkmm.h>
#include <stdint.h>
#include <cstdlib>
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

/* Classes */
template <class GtkType>
class AtlasApp
{
public:

    /* ************************************
     * ***** APPLICATION CONSTRUCTORS *****
     * ************************************
     */

    AtlasApp(void)
    {
        widget   = NULL;
        size     = 0;
        callback = NULL;
    }

    AtlasApp(GtkType *w)
    {
        widget   = Gtk::manage(w);
        size     = 1;
        callback = NULL;
    }

    AtlasApp(GtkType *w, size_t s)
    {
        widget   = Gtk::manage(w);
        size     = s;
        callback = NULL;
    }

    AtlasApp(GtkType *w, size_t s, bool (*f)(void*))
    {
        widget   = Gtk::manage(w);
        size     = s;
        callback = f;
    }

    /* ***************************************
     * ***** APPLICATION INITIALIZATIONS *****
     * ***************************************
     */

    void init(GtkType *w)
    {
        widget   = Gtk::manage(w);
        size     = 1;
        callback = NULL;
    }

    void init(GtkType *w, bool (*f)(void*))
    {
        widget   = Gtk::manage(w);
        size     = 1;
        callback = f;
    }

    void init(GtkType *w, size_t s)
    {
        widget   = Gtk::manage(w);
        size     = s;
        callback = NULL;
    }

    void init(GtkType *w, size_t s, bool (*f)(void*))
    {
        widget   = Gtk::manage(w);
        size     = s;
        callback = f;
    }

    /* *******************************
     * ***** ATTACH APPLICATIONS *****
     * *******************************
     */

    template <typename GtkAppType>
    void attach(AtlasApp<GtkAppType> &a)
    {
        attach(a.widget, a.size);
    }

    template <typename GtkAppType>
    void attach(AtlasApp<GtkAppType> &a, AtlasAlign::AlignType align)
    {
        attach(a.widget, a.size, align);
    }

    template <typename GtkAppType>
    void attach(GtkAppType *w, size_t s)
    {
        if ( !dynamic_cast<Gtk::Container*>(widget) )
            return;

        size_t i;
        for ( i = 0; i < s; ++i )
            static_cast<Gtk::Container*>(widget)->add(w[i]);
    }

    template <typename GtkAppType>
    void attach(GtkAppType *w, size_t s, AtlasAlign::AlignType align)
    {
        if ( !dynamic_cast<Gtk::Container*>(widget) ) {
            std::cout << "Widget is not a container" << std::endl;
            return;
        }

        size_t i;
        switch ( align ) {
        case AtlasAlign::LEFT:
            for ( i = 0; i < s; ++i )
                static_cast<Gtk::Box*>(widget)->pack_start(w[i], Gtk::PACK_SHRINK);
            return;
        case AtlasAlign::CENTER:
            for ( i = 0; i < s; ++i )
                static_cast<Gtk::Box*>(widget)->set_center_widget(w[i]);
            return;
        case AtlasAlign::RIGHT:
            for ( i = 0; i < s; ++i )
                static_cast<Gtk::Box*>(widget)->pack_end(w[i], Gtk::PACK_SHRINK);
            return;
        }
    }

    /* ******************************
     * ***** FUNCTION CALLBACKS *****
     * ******************************
     */

    /* Connect application callback function */
    void connect_callback(uint16_t time)
    {
        connect_callback(update, time);
    }

    void connect_callback(bool (*f)(void*), uint16_t time)
    {
        sigc::slot<bool, void*> slot = sigc::ptr_fun(f);
        Glib::signal_timeout().connect_seconds(sigc::bind<void*>(slot, static_cast<void*>(widget)), time);
    }

    /* ********************************* */


    /* ************************************************************************** */
    /* Callback function to periodically update the application icon */
    bool update(void *w)
    {
        // std::string type = AtlasConfig::fetch(sac, "type");
        // std::cout << type << " " << "update" << std::endl;
        // if ( type.compare("image") == 0 )
        //     static_cast<Gtk::Image*>(w)->set(this->get_icon());
        // else if ( type.compare("label") == 0 )
        //     static_cast<Gtk::Label*>(w)->set_text(get_text());
        return true;
    }

    /* *********************************
     * ***** APPLICATION VARIABLES *****
     * *********************************
     */

    GtkType *widget;
    size_t   size;
    bool   (*callback)(void*);
    // struct NameApp fucker;
};


    // std::string type;
    // unsigned int size;

    // /* add signal */

    // std::string  command;
    // std::string  directory;
    // unsigned int update;

    // /* NameAppSpace */
    // int xmargin;
    // int ymargin;
    // int xpadding;
    // int ypadding;

    // /* NameAppText */
    // std::string  format;
    // std::string  font;
    // unsigned int size

    // /* NameAppColor */
    // std::string background;
    // std::string foreground;

#endif /* ATLAS_APP_H */
