#ifndef ATLAS_APPLE_H
#define ATLAS_APPLE_H

#include "AtlasAlignType.h"
#include <stdint.h>
#include <gtkmm.h>
#include <string>
#include <vector>

typedef std::string (*AtlasGetFunc)(void);
typedef int         (*AtlasEventFunc)(void*);
typedef int         (*AtlasSignalFunc)(unsigned int);

struct NameApp {
    std::string             name;
    std::string             type;
    AtlasAlign::AlignType   align;
    unsigned int            length;
    int                     focus;
    AtlasGetFunc            getstr;
    AtlasEventFunc          event;
    AtlasSignalFunc         signal;
    void                   *app;
};

class AtlasApple
{
public:
    AtlasApple();

    void        create(std::string name, AtlasGetFunc getstr);
    void        create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event);
    void        create(std::string name, AtlasGetFunc getstr, AtlasSignalFunc signal);
    void        create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal);

    NameApp        *app;

private:
    // static int           doimage(NameApp *node, int val);
    // static int           dolabel(NameApp *node, int val);
    // static bool          update(NameApp *node);
    // static bool          update(NameApp *node, int val);
    // static Gtk::Widget * get_widget(NameApp *node);

    int                  new_app(void);
    // int                  set_name(std::string name);
    // int                  set_func(AtlasGetFunc getstr);
    // int                  set_func(AtlasGetFunc getstr, AtlasEventFunc event);
    // int                  set_func(AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal);
    // int                  set_type(void);
    int                  set_image(void **widget);
    // static int           set_focuser(Gtk::Widget &widget, int index, int focus, std::string color);
    // static int           set_label(NameApp *node, void **widget);
    // static int           set_label(NameApp *node);

    int                  init_widget(void **widget);
    int                  set_widget(void);
    int                  set_widget(void **widget);
    // int                  set_align(void);
    // int                  set_length(void);
    // static int           set_focus(NameApp *node, int index);
    // int                  set_focus(void);
    // int                  set_update(void);
    // int                  clear(void);
};

#endif
