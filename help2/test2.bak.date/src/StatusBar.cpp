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
#include <iostream>
#include <cstdlib>

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <string>



// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

StatusBar::StatusBar() :
    bar(Gtk::ORIENTATION_HORIZONTAL, 5),
    // m_Label_Normal("_This is a Normal label", true),
    m_Label_Multi("This is a Multi-line label.\nSecond line\nThird line"),
    m_Label_Left("This is a Left-Justified\nMulti-line label.\nThird line"),
    m_Label_Right("This is a Right-Justified\nMulti-line label.\nThird line")
{
    set_title("Atlas");
    set_border_width(5);
    set_default_size(1366, 100);
    
    add(bar);
    
    m_Label_Normal.set_text("_This is a Normal label");
        
    bar.pack_start(m_Label_Normal, Gtk::PACK_SHRINK);
    bar.pack_end(m_Label_Multi, Gtk::PACK_SHRINK);
    bar.pack_end(m_Label_Left, Gtk::PACK_SHRINK);
    bar.pack_start(m_Label_Right, Gtk::PACK_SHRINK);
    
    m_Label_Left.set_justify(Gtk::JUSTIFY_LEFT);
    m_Label_Right.set_justify(Gtk::JUSTIFY_RIGHT);
}


StatusBar::~StatusBar() {
}


// Initialize image widgets
BarLabel::BarLabel(Gtk::Box *ats, std::string (*ploob)()) {
// BarLabel::BarLabel(Gtk::Box *ats, Glib::ustring text) {
    
    label = new Gtk::Label(ploob());
    
    // printf("Done: %s\n", label->get_text().c_str());
    // printf("%p\n", label);
    // Glib::signal_timeout().connect_seconds(sigc::mem_fun(this, &BarLabel::incr), 1);
    
    // sigc::slot<void, int> sl = sigc::mem_fun(my_foo, &foo::bar);
    // sigc::slot<bool, Gtk::Label*> func = sigc::mem_fun(*this, &BarLabel::incr);
    // Glib::signal_timeout().connect_seconds(sigc::bind<Gtk::Label*>(func, label), 1);
    
    sigc::slot<bool, Gtk::Label*, std::string(*)()> func = 
        sigc::mem_fun(*this, &BarLabel::update);
    Glib::signal_timeout().connect_seconds(sigc::bind<Gtk::Label*, std::string(*)()>(func, label, ploob), 1);
    
    ats->set_center_widget(*label);
    
    // printf("%p\n", label);
    
    count = 0;
    stuff = "0";
    
    // event    = gtk_event_box_new();
    // get_icon = func;
}

bool BarLabel::update(Gtk::Label *orig_label, std::string (*getter)()) {
    orig_label->set_text(getter());    
    // Glib::signal_timeout().connect_seconds(sigc::ptr_fun(getter), 1);
    return true;
}


bool BarLabel::incr(Gtk::Label *orig_label) {
    ++count;
    
    switch (count) {
    case 1: 
        stuff = "1";
        break;
    case 2: 
        stuff = "2";
        break;
    case 3: 
        stuff = "3";
        break;
    case 4: 
        stuff = "4";
        break;
    case 5: 
        stuff = "5";
        break;
    case 6: 
        stuff = "6";
        break;
    case 7: 
        stuff = "7";
        break;
    case 8: 
        stuff = "8";
        break;
    case 9: 
        stuff = "9";
        break;
    default:
        stuff = "1";
        count = 1;
    }
    
    // printf("%s\n", stuff.c_str());
    // printf("%p\n", orig_label);

    
    orig_label->set_text(stuff);
    // printf("Done: %s\n", orig_label->get_text().c_str());
    
    return true;
}



BarLabel::~BarLabel() {
}

// Return current brightness level
int StatusBar::get_percent(std::string cmd) {
    
    // Get output from command
    FILE *handle = popen(cmd.c_str(), "r");
    char output[20];
    fgets(output, sizeof(output), handle);    
    fclose(handle);
    
    // Convert command output to integer volume level
    int i = 0;
    int j = 0;
    char level[4];
    memset(level, 0, sizeof(level));
    
    while ( (output[i] != 0) && (j != (sizeof(level)-1)) ) {
        if ( (output[i] >= '0') && (output[i] <= '9') ) {
            level[j] = output[i];
            if ( atoi(level) > 100 )
                level[j] = '\0';
            ++j;
        }
        
        ++i;
    }
    printf("%s: %s\n", cmd.c_str(), level);
    return atoi(level);
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



// // Initialize image widgets
// void Statusbar::Image::init(std::string (*func)()) {
//     img      = gtk_image_new();
//     event    = gtk_event_box_new();
//     get_icon = func;
// }



// gboolean Statusbar::Image::set(gpointer data) {
    
//     // Extract widget from pointer
//     GList *children = gtk_container_get_children(GTK_CONTAINER(event));
    
//     // Get icon location
//     std::string path = get_icon();
//     gtk_image_set_from_file(GTK_IMAGE(children->data), path.c_str());
    
//     // Free memory
//     g_list_free(children);
    
//     return TRUE;
// }


// GCallback Statusbar::Image::seta() {
    
//     // Extract widget from pointer
//     GList *children = gtk_container_get_children(GTK_CONTAINER(event));
    
//     // Get icon location
//     std::string path = get_icon();
//     gtk_image_set_from_file(GTK_IMAGE(children->data), path.c_str());
    
//     // Free memory
//     g_list_free(children);
    
//     return 0;
// }



// void Statusbar::Image::setters(GtkWidget *bar, int section, int timer) {
    
//     // Set volume icon
//     std::string path = get_icon();
//     gtk_image_set_from_file(GTK_IMAGE(img), path.c_str());
    
//     // Enable events on widget
//     GCallback (Statusbar::Image::*arg)();
//     arg = &Statusbar::Image::seta;
    
//     gtk_widget_add_events(event, GDK_ENTER_NOTIFY_MASK);
//     g_signal_connect(G_OBJECT(event), "enter-notify-event", arg, NULL);
    
//     if ( timer > 0 );
//     //     g_timeout_add_seconds(timer, (GSourceFunc)*set, event);
    
//     // Display the widget
//     gtk_container_add(GTK_CONTAINER(event), img);
//     if ( section == 1 )
//         gtk_box_pack_end(GTK_BOX(bar), event, 0, 0, 5);
    
//     // Display widgets
//     gtk_widget_show(event);
//     gtk_widget_show(img);
// }
