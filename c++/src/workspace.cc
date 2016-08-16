/* *****************************************************************************
 * 
 * Name:    workspace.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: A workspace application for Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "workspace.h"
#include "atlas.h"

/* Private functions */
static void     signalworkspace(uint32_t key);
static bool     setworkspacelabel(void);
static uint32_t getworkspacelabel(void);

/* Globals */
static Gtk::Label *widget = NULL;


/* ************************************************************************** */
/* Create workspace application */
AtlasApp & workspaces(void)
{
    uint8_t size = 5;
    uint8_t i;
    widget = new Gtk::Label[size];

    for (i = 0; i < size; ++i ) {
        widget[i].set_label(std::to_string(i+1));
        atlas::app::set_padding(widget[i], 5, 0);
        atlas::app::set_background(widget[i], "#333333");
        atlas::app::set_font(widget[i], "GohuFont", 9);
    }
    setworkspacelabel();

    static AtlasApp app(widget, size, atlas::align::LEFT);
    app.set_signal(signalworkspace, ATLAS_SIG_MON);
    return app;
}

/* ************************************************************************** */
void signalworkspace(uint32_t key)
{
    setworkspacelabel();
}

/* ************************************************************************** */
/* Set workspace label */
bool setworkspacelabel(void)
{
    uint32_t    current = getworkspacelabel();
    uint32_t    i;
    std::string color;
    for (i = 0; i < 5; ++i) {
        if (i == current)
            color = "#FFFFFF";
        else
            color = "#999999";
        atlas::app::set_foreground(widget[i], color);
    }

    return true;
}

/* ************************************************************************** */
/* Return workspace icon path */
uint32_t getworkspacelabel(void)
{
    long current;
    getdefaultatomval("_NET_CURRENT_DESKTOP", &current);
    return (uint32_t)current;
}
