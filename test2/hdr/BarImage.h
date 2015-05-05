// ============
// Header Guard
// ============

#ifndef BARIMAGE_H
#define BARIMAGE_H


// ========
// Includes
// ========

#include "../hdr/StatusBar.h"
#include <gtkmm.h>
#include <string>


// =======
// Classes
// =======

class BarImage {
 public:
    BarImage();
    BarImage(Gtk::Box *bar, std::string text);
    
    void          set(std::string (*func)());
    void          position(StatusBar::Section sec);
    void          padding(int x, int y);
    void          background(std::string background);
    void          foreground(std::string foreground);
    void          update(std::string (*func)(), int time);
    bool          timeout(Gtk::Image *orig, std::string (*func)());
    
    Gtk::Box      *box;
    Gtk::Image    *item;
};

#endif
