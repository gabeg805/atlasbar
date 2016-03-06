/* *****************************************************************************
 * 
 * Name:    AtlasEvent.cc
 * Class:   <AtlasEvent>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: 
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

#include "AtlasEvent.h"
#include "AtlasConfig.h"
#include "AtlasApple.h"
#include "AtlasAppGeneric.h"
#include <fcntl.h>
#include <gtkmm.h>
#include <semaphore.h>
#include <stdint.h>
#include <sys/stat.h>
#include <iostream>
#include <string>
#include <vector>

/* ************************************************************************** */
/* Update an app by their name*/
void AtlasEvent::signal(int sig)
{
    /* Retrieve value from semaphore */
    sem_t        *sem = sem_open("/semi", O_RDONLY, 0644, 0);
    if ( sem == NULL )
        return;

    uint16_t key;
    sem_getvalue(sem, (int*)&key);
    printf("sig: 0x%0x\n", key);

    /* Update statusbar and call application command */
    std::vector<NameApp*>::iterator app;
    for ( app = container.begin(); app != container.end(); ++app ) {
        if ( (*app)->signal != NULL ) {
            int ret = (*app)->signal(key);
            if ( ret == 0 )
                AtlasEvent::update(*app);
            else if ( ret > 0 )
                AtlasEvent::update(*app, ret);
            else
                ;
        }
    }
}

/* ************************************************************************** */
/* Update applications */
bool AtlasEvent::update(NameApp *node)
{
    return AtlasEvent::update(node, 0);
}        

/* ************************************************************************** */
/* Update applications */
bool AtlasEvent::update(NameApp *node, int ret)
{
    if ( node == NULL )
        return false;

    std::string type = node->type;
    if ( type.compare("image") == 0 )
        AtlasEvent::doimage(node, ret);
    else if ( type.compare("label") == 0 )
        AtlasEvent::dolabel(node, ret);
    else
        ;

    return true;
}

/* ************************************************************************** */
int AtlasEvent::doimage(NameApp *app, int ret)
{
    if ( ret == 0 ) {
        Gtk::Widget              *widget = AtlasEvent::get_widget(app);
        std::vector<std::string>  vec    = AtlasConfig::parse(app->getstr(), '|');
        int                       len    = app->length;
        int                       i;
        for ( i = 0; i < len; ++i )
            static_cast<Gtk::Image*>(widget)[i].set(vec[i]);
        return 0;
    }

    return 0;
}

/* ************************************************************************** */
int AtlasEvent::dolabel(NameApp *app, int ret)
{
    std::cout << "doing label: " << app->name << std::endl;
    std::cout << "setting focus: " << ret << std::endl;
    AtlasEvent::set_focus(app, ret);
    AtlasEvent::set_label(app);
    std::cout << "Workspace: " << ret << std::endl;

    return 0;
}

/* ************************************************************************** */
/* Initialize and set a label application */
int AtlasEvent::set_label(NameApp *node)
{
    void *widget = AtlasEvent::get_widget(node);
    return AtlasEvent::set_label(node, &widget);
}

/* ************************************************************************** */
/* Initialize and set a label application */
int AtlasEvent::set_label(NameApp *node, void **widget)
{
    Gtk::Label               *label       = static_cast<Gtk::Label*>(*widget);
    std::string               name        = node->name;
    int                       len         = node->length;
    int                       focus       = node->focus;
    std::vector<std::string>  strvec      = AtlasConfig::parse(node->getstr(), '|');
    std::string               font        = AtlasConfig::fetch(name, "font");
    int                       size        = AtlasConfig::fetch_int(name, "font-size");
    std::string               margin      = AtlasConfig::fetch(name, "margin");
    std::string               padding     = AtlasConfig::fetch(name, "padding");
    std::string               background  = AtlasConfig::fetch(name, "background");
    std::string               foreground  = AtlasConfig::fetch(name, "foreground");
    std::string               focus_color = AtlasConfig::fetch(name, "focus-color");
    int i;
    for ( i = 0; i < len; ++i ) {
        label[i].set_text(strvec[i]);
        AtlasAppGeneric::set_font(label[i], font, size);
        AtlasAppGeneric::set_margin(label[i], margin);
        AtlasAppGeneric::set_padding(label[i], padding);
        AtlasAppGeneric::set_background(label[i], background);
        AtlasAppGeneric::set_foreground(label[i], foreground);
        set_focuser(label[i], i, focus, focus_color);
    }

    return 0;
}

/* ************************************************************************** */
int AtlasEvent::set_focuser(Gtk::Widget &widget, int index, int focus, std::string color)
{
    if ( focus < 0 )
        return -1;
    else {
        if ( index == focus )
            AtlasAppGeneric::set_foreground(widget, color);
        else
            return -1;
    }
    return 0;
}

/* ************************************************************************** */
/* Set the number of sub-applications, within the application */
int AtlasEvent::set_focus(NameApp *node, int index)
{
    node->focus = index;
    return 0;
}

/* ************************************************************************** */
/* Return the application corresponding to the given node */
Gtk::Widget * AtlasEvent::get_widget(NameApp *node)
{
    if ( node == NULL )
        return NULL;

    std::string event = AtlasConfig::fetch(node->name, "event");
    if ( event.empty() )
        return static_cast<Gtk::Widget*>(node->app);
    else
        return static_cast<Gtk::EventBox*>(node->app)->get_child();
}
