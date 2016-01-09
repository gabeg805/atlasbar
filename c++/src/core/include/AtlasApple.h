#ifndef ATLAS_APPLE_H
#define ATLAS_APPLE_H

#include "AtlasAlignType.h"
#include <gtkmm.h>
#include <string>

struct NameApp {
    std::string             name;
    std::string             type;
    AtlasAlign::AlignType   align;
    unsigned int            length;
    std::string           (*getstr)(void);
    bool                  (*event)(void*);
    bool                  (*signal)(unsigned int);
    void                   *app;
    struct NameApp         *next;
};

extern NameApp *head;


class AtlasApple
{
public:
    AtlasApple();

    NameApp * get_head(void);
    NameApp * get_node(void);
    static Gtk::Widget * get_app(NameApp *node);
    static int           update(std::string name);
    static void          signal(int sig);
    int       set_name(NameApp *node, std::string name);
    int       set_func(NameApp *node, std::string (*getstr)(void));
    int       set_func(NameApp *node, std::string (*getstr)(void), bool (*event)(void*));
    int       set_func(NameApp *node, std::string (*getstr)(void), bool (*event)(void*), bool (*signal)(unsigned int));
    int       set_type(NameApp *node);
    int       set_app(void **app, std::string type, std::string str);
    int       set_app(NameApp *node);
    int       set_align(NameApp *node);
    int       set_length(NameApp *node);
    int       set_update(NameApp *node);
    int       set_margin(NameApp *node);
    int       set_padding(NameApp *node);
    int       set_background(NameApp *node);
    int       set_foreground(NameApp *node);
    int       set_font(NameApp *node);
    NameApp * clear_node(NameApp *node);

    void creation(std::string name, std::string (*getstr)(void));
    void creation(std::string name, std::string (*getstr)(void), bool (*event)(void*));
    void creation(std::string name, std::string (*getstr)(void), bool (*event)(void*), bool (*signal)(unsigned int));
};

#endif
