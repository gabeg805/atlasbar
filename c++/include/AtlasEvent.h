#ifndef ATLAS_EVENT_H
#define ATLAS_EVENT_H

#include "AtlasApple.h"
#include <gtkmm.h>
#include <string>
#include <vector>

namespace AtlasEvent
{
    void          signal(int sig);

    int           doimage(NameApp *node, int val);
    int           dolabel(NameApp *node, int val);
    bool          update(NameApp *node);
    bool          update(NameApp *node, int val);
    Gtk::Widget * get_widget(NameApp *node);

    int           set_focuser(Gtk::Widget &widget, int index, int focus, std::string color);
    int           set_label(NameApp *node, void **widget);
    int           set_label(NameApp *node);

    int           set_focus(NameApp *node, int index);
};

extern std::vector<NameApp*> container;

#endif /* ATLAS_EVENT_H */
