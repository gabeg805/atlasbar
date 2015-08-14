/* *****************************************************************************
 * 
 * Name:    Workspace.h
 * Class:   <Workspace>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas workspace indicator applicationx.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_WORKSPACE_H
#define ATLAS_WORKSPACE_H

/* Includes */
#include "AtlasApp.h"
#include <gtkmm.h>
#include <stdint.h>
#include <string>
#include <vector>

/* Classes */
class Workspace:
    public AtlasApp<Gtk::Label>
{
public:
    void        create();
    static bool update(void *w);
    static void update(Gtk::Label *w, uint8_t workspace);

    static uint8_t screen;

private:
    static std::vector<std::string> get_tags(void);
    static uint8_t                  get_tag_size(void);
};

/* Global object */
extern Workspace workspace;

#endif /* ATLAS_WORKSPACE_H */
