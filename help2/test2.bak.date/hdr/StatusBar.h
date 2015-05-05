// Header guard
#ifndef STATUSBAR_H
#define STATUSBAR_H

// Includes
#include <gtkmm.h>
#include <string>
#include <stdint.h>


// =======
// Classes
// =======

/* gboolean      set_icon(gpointer eventbox, std::string (*get_icon)()); */
// PangoAttrList *attr;
// Left = -1; Middle = 0; Right = 1;

class StatusBar : public Gtk::Window {
 public:
    StatusBar();
    virtual       ~StatusBar();
    
    int           get_percent(std::string cmd);
    
    /* Gtk::Window   win; */
    Gtk::Box      bar;
    
    //Child widgets:
    Gtk::Frame m_Frame_Normal, m_Frame_Multi, m_Frame_Left, m_Frame_Right;
    Gtk::Label m_Label_Normal, m_Label_Multi, m_Label_Left, m_Label_Right;
};

class BarLabel {
 public:
    BarLabel(Gtk::Box *ats, std::string (*ploob)());
    /* BarLabel(Gtk::Box *ats, Glib::ustring text); */
    virtual ~BarLabel();
    
    bool     update(Gtk::Label *orig_label, std::string (*getter)());
    bool     incr(Gtk::Label *orig_label);
    /* bool    incr(); */
    
    Gtk::Label    *label;
    Glib::ustring stuff;
    int count;
};
    
    

extern StatusBar Atlas;

#endif
