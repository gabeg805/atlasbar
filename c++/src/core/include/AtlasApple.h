#ifndef ATLAS_APPLE_H
#define ATLAS_APPLE_H

#include "AtlasAlignType.h"
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
    struct NameApp         *next;
};

class AtlasApple
{
public:
    AtlasApple();

    void        create(std::string name, AtlasGetFunc getstr);
    void        create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event);
    void        create(std::string name, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal);
    int         attach_all_to_parent(Gtk::Box *parent);
    static int  attach_to_parent(Gtk::Box &parent, NameApp *node);
    static void signal(int sig);
    static int  set_background(Gtk::Widget &app, std::string background);
    static int  set_foreground(Gtk::Widget &app, std::string foreground);
    static int  set_margin(Gtk::Widget &app, int xmargin, int ymargin);
    static int  set_padding(Gtk::Misc &app, int xpadding, int ypadding);
    static int  set_font(Gtk::Widget &app, std::string font);
    static int  set_font(Gtk::Widget &app, std::string font, int size);
    static int  set_orientation(Gtk::Orientable &app, std::string orientation);
    static int  set_size(Gtk::Window &app, int width, int height);

private:
    static int           doimage(NameApp *node, int val);
    static int           dolabel(NameApp *node, int val);
    static bool          update(NameApp *node);
    static bool          update(NameApp *node, int val);
    static Gtk::Widget * get_app(NameApp *node);
    Gtk::Widget *        get_app(std::string name);
    int                  set_next(NameApp **node);
    int                  set_name(NameApp *node, std::string name);
    int                  set_func(NameApp *node, AtlasGetFunc getstr);
    int                  set_func(NameApp *node, AtlasGetFunc getstr, AtlasEventFunc event);
    int                  set_func(NameApp *node, AtlasGetFunc getstr, AtlasEventFunc event, AtlasSignalFunc signal);
    int                  set_type(NameApp *node);
    int                  set_image(NameApp *node, void **app);
    static int                  set_focuser(Gtk::Widget &app, int index, int focus, std::string color);
    static int                  set_label(NameApp *node, void **app);
    static int                  set_label(NameApp *node);
    int                  set_app(NameApp *node, void **app);
    int                  init_app(NameApp *node, void **app);
    int                  set_app(NameApp *node);
    int                  set_align(NameApp *node);
    int                  set_length(NameApp *node);
    static int                  set_focus(NameApp *node, int index);
    static int                  set_focus(NameApp *node);
    int                  set_update(NameApp *node);

    int                  set_margin(std::string name, Gtk::Widget &app);
    int                  set_padding(std::string name, Gtk::Misc &app);
    int                  set_background(std::string name, Gtk::Widget &app);
    int                  set_foreground(std::string name, Gtk::Widget &app);
    int                  set_font(std::string name, Gtk::Widget &app);

    int                  clear(NameApp **node);

    static NameApp *head;
    NameApp *current;
};

#endif
