/* *****************************************************************************
 * 
 * Name:    atlasapp.cc
 * Class:   <AtlasApp>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Application.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlasapp.h"
#include "atlasalign.h"
#include "atlassignal.h"
#include <gtkmm.h>
#include <stdint.h>

/* ************************************************************************** */
/* Constructor */
AtlasApp::AtlasApp(void)
{
    this->init(NULL, 0, atlas::align::NONE);
}

/* ************************************************************************** */
/* Constructor */
AtlasApp::AtlasApp(Gtk::Widget *widget)
{
    this->init(widget, 1, atlas::align::NONE);
}

/* ************************************************************************** */
/* Constructor */
AtlasApp::AtlasApp(Gtk::Widget *widget, atlas::align_t align)
{
    this->init(widget, 1, align);
}

/* ************************************************************************** */
/* Constructor */
AtlasApp::AtlasApp(Gtk::Widget *widget, uint8_t size, atlas::align_t align)
{
    this->init(widget, size, align);
}

/* ************************************************************************** */
/* Initialize application elements */
void AtlasApp::init(Gtk::Widget *widget, uint8_t size, atlas::align_t align)
{
    this->app         = new atlas::app_t();
    this->app->widget = widget;
    this->app->size   = size;
    this->app->signal = NULL;
    this->app->align  = align;
}

/* ************************************************************************** */
/* Set application widget */
void AtlasApp::set_widget(Gtk::Widget *widget)
{
    this->app->widget = widget;
}

/* ************************************************************************** */
/* Set number of widgets in application */
void AtlasApp::set_size(uint8_t size)
{
    this->app->size = size;
}

/* ************************************************************************** */
/* Set application signal callback function */
void AtlasApp::set_signal(atlas::clbk_t callback, atlas::key_t key)
{
    if ( this->app->signal == NULL )
        this->app->signal = new atlas::sig_t();
    this->app->signal->callback = callback;
    this->app->signal->key      = key;
}

/* ************************************************************************** */
/* Set statusbar alignment */
void AtlasApp::set_align(atlas::align_t align)
{
    this->app->align = align;
}

/* ************************************************************************** */
/* Return application widget */
Gtk::Widget * AtlasApp::get_widget(void)
{
    return this->app->widget;
}

/* ************************************************************************** */
/* Return number of widgets in application */
uint8_t AtlasApp::get_size(void)
{
    return this->app->size;
}

/* ************************************************************************** */
/* Return application signal callback function */
atlas::sig_t * AtlasApp::get_signal(void)
{
    return ( this->app->signal != NULL ) ? this->app->signal : NULL;
}

/* ************************************************************************** */
/* Return application signal key */
atlas::key_t AtlasApp::get_key(void)
{
    return ( this->app->signal != NULL ) ? this->app->signal->key : 0;
}

/* ************************************************************************** */
/* Return statusbar alignment */
atlas::align_t AtlasApp::get_align(void)
{
    return this->app->align;
}
