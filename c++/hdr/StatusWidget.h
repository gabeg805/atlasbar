// -*-c++-*-

// ============
// Header Guard
// ============

#ifndef STATUSWIDGET_H
#define STATUSWIDGET_H


// ========
// Includes
// ========

#include <gtkmm.h>
#include <gdkmm.h>
#include <pangomm/fontdescription.h>
#include <string>


// =======
// Classes
// =======

class StatusWidget {
public:
    enum Section { ALIGN_LEFT=1, ALIGN_CENTER, ALIGN_RIGHT };
    
    
    
    // Set the region of the statusbar to display the item (left/center/right);
    template <typename atlas_w> 
    static void attach(Gtk::Box *box, atlas_w *widg, StatusWidget::Section section) {
        if ( section == StatusWidget::ALIGN_LEFT )
            box->pack_start(*widg, Gtk::PACK_SHRINK);
    
        if ( section == StatusWidget::ALIGN_CENTER)
            box->set_center_widget(*widg);
    
        if ( section == StatusWidget::ALIGN_RIGHT)
            box->pack_end(*widg, Gtk::PACK_SHRINK);
    }
    
    
    
    // set the background color of the statusbar item
    template <typename atlas_w>
    static void background(atlas_w *widg, std::string background) {
        Gdk::RGBA color(background);
        widg->override_background_color(color, Gtk::STATE_FLAG_NORMAL);
    }
    
    
    
    // Set the foreground color of the statusbar item
    template <typename atlas_w>
    static void foreground(atlas_w *widg, std::string foreground) {
        Gdk::RGBA color(foreground);
        widg->override_color(color, Gtk::STATE_FLAG_NORMAL);
    }
    
    
    
    // Set the statusbar item with the given font and size
    static void font(Gtk::Label *label, std::string font, int size) {
        Pango::FontDescription desc;
        desc.set_family(font);
        desc.set_size(size * PANGO_SCALE);
    
        label->override_font(desc);
    }
    
    
    
    // Set the statusbar item with the given font and size
    template <typename atlas_w>
    static void padding(atlas_w *widg, int x, int y) {
        widg->set_padding(x, y);
    }
};

#endif
