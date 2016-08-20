/* *****************************************************************************
 * 
 * Name:    atlasapp.h
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

/* Header guard */
#ifndef ATLAS_APP_H
#define ATLAS_APP_H

/* Includes */
#include "atlasalign.h"
#include "atlassignal.h"
#include <gtkmm.h>
#include <stdint.h>

/* Namespace */
namespace atlas
{
    /* Structures */
    typedef struct
    {
        Gtk::Widget    *widget;
        atlas::sig_t   *signal;
        atlas::align_t  align;
        uint8_t         size;
    } app_t;
};

/* Classes */
class AtlasApp
{
public:
    AtlasApp(void);
    AtlasApp(Gtk::Widget *widget);
    AtlasApp(Gtk::Widget *widget, atlas::align_t align);
    AtlasApp(Gtk::Widget *widget, uint8_t size, atlas::align_t align);

    void set_widget(Gtk::Widget *widget);
    void set_size(uint8_t size);
    void set_signal(atlas::clbk_t callback, atlas::key_t key);
    void set_align(atlas::align_t align);

    Gtk::Widget *  get_widget(void);
    uint8_t        get_size(void);
    atlas::sig_t * get_signal(void);
    atlas::key_t   get_key(void);
    atlas::align_t get_align(void);

private:
    void init(Gtk::Widget *widget, uint8_t size, atlas::align_t align);

    atlas::app_t *app;
};

#endif /* ATLAS_APP_H */
