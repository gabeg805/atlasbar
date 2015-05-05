// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     StatusBar.cpp
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/StatusBar.h"
// 
// 
// PURPOSE:
// 
//     Write shit.
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg May 02 2014 <> Removed excessive parts of the header.
//                          Made every widget attach to one Application, instead of 
//                          being separate entities.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/StatusBar.h"

#include <gtkmm.h>
#include <gdkmm.h>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;



// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

StatusBar::StatusBar() :
    Gtk::Window(Gtk::WINDOW_POPUP),
    bar(Gtk::ORIENTATION_HORIZONTAL, 5)
{
    set_title("Atlas");
    set_default_size(1366, 20);
    
    background = "#333333";
    foreground = "white";
    
    Gdk::RGBA back(background);
    Gdk::RGBA fore(foreground);
    
    override_background_color(back, Gtk::STATE_FLAG_NORMAL);
    override_color(fore, Gtk::STATE_FLAG_NORMAL);
    
    add(bar);
}

// void Statusbar::init(Glib::RefPtr<Gtk::Application> mainApp) {
// void Statusbar::init() {
    // win  = gtk_window_new(GTK_WINDOW_POPUP);
    // bar  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    // attr = pango_attr_list_new();

    // GdkRGBA color  = {0.19, 0.19, 0.23, 1};
    // GdkRGBA colorq = {1, 1, 1, 1};
    
    // gtk_window_move(GTK_WINDOW(win), 0, 0);
    // gtk_window_set_default_size(GTK_WINDOW(win), 1366, 20);
    // gtk_widget_override_background_color(win, GTK_STATE_FLAG_NORMAL, &color);
    // gtk_widget_override_color(win, GTK_STATE_FLAG_NORMAL, &colorq);
    
    // // GTK signal
    // gtk_container_add(GTK_CONTAINER(win), bar);
    // g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // // Define text attributes
    // char font[] = "Inconsolata";
    // int fsize  = 8*1024;
    
    // PangoAttribute *attrFont = pango_attr_family_new(font);
    // PangoAttribute *attrSize = pango_attr_size_new(fsize);
    // PangoAttribute *attrColor = pango_attr_foreground_new(65535, 65535, 65535);
    
    // // Add attributes to the list (and increase the reference counter)
    // attr = pango_attr_list_ref(attr);
    // attr = pango_attr_list_ref(attr);
    // pango_attr_list_insert(attr, attrSize);
    // pango_attr_list_insert(attr, attrFont);
    // pango_attr_list_insert(attr, attrColor);
    // win.show_all_children();
// }
