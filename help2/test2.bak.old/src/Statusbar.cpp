// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     Statusbar.cpp
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/Statusbar.h"
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
#include "../hdr/Statusbar.h"

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <string>


// ///////////////////////////////////
// ///// DISPLAY ATLAS STATUSBAR /////
// ///////////////////////////////////

void Statusbar::init() {
    win  = gtk_window_new(GTK_WINDOW_POPUP);
    bar  = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    attr = pango_attr_list_new();

    GdkRGBA color  = {0.19, 0.19, 0.23, 1};
    GdkRGBA colorq = {1, 1, 1, 1};
    
    gtk_window_move(GTK_WINDOW(win), 0, 0);
    gtk_window_set_default_size(GTK_WINDOW(win), 1366, 20);
    gtk_widget_override_background_color(win, GTK_STATE_FLAG_NORMAL, &color);
    gtk_widget_override_color(win, GTK_STATE_FLAG_NORMAL, &colorq);
    
    // GTK signal
    gtk_container_add(GTK_CONTAINER(win), bar);
    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Define text attributes
    char font[] = "Inconsolata";
    int fsize  = 8*1024;
    
    PangoAttribute *attrFont = pango_attr_family_new(font);
    PangoAttribute *attrSize = pango_attr_size_new(fsize);
    PangoAttribute *attrColor = pango_attr_foreground_new(65535, 65535, 65535);
    
    // Add attributes to the list (and increase the reference counter)
    attr = pango_attr_list_ref(attr);
    attr = pango_attr_list_ref(attr);
    pango_attr_list_insert(attr, attrSize);
    pango_attr_list_insert(attr, attrFont);
    pango_attr_list_insert(attr, attrColor);
}



// Return current brightness level
int Statusbar::get_percent(std::string cmd) {
    
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



// Initialize image widgets
void Statusbar::Image::init(std::string (*func)()) {
    img      = gtk_image_new();
    event    = gtk_event_box_new();
    get_icon = func;
}



gboolean Statusbar::Image::set(gpointer data) {
    
    // Extract widget from pointer
    GList *children = gtk_container_get_children(GTK_CONTAINER(event));
    
    // Get icon location
    std::string path = get_icon();
    gtk_image_set_from_file(GTK_IMAGE(children->data), path.c_str());
    
    // Free memory
    g_list_free(children);
    
    return TRUE;
}


GCallback Statusbar::Image::seta() {
    
    // Extract widget from pointer
    GList *children = gtk_container_get_children(GTK_CONTAINER(event));
    
    // Get icon location
    std::string path = get_icon();
    gtk_image_set_from_file(GTK_IMAGE(children->data), path.c_str());
    
    // Free memory
    g_list_free(children);
    
    return 0;
}



void Statusbar::Image::setters(GtkWidget *bar, int section, int timer) {
    
    // Set volume icon
    std::string path = get_icon();
    gtk_image_set_from_file(GTK_IMAGE(img), path.c_str());
    
    // Enable events on widget
    GCallback (Statusbar::Image::*arg)();
    arg = &Statusbar::Image::seta;
    
    gtk_widget_add_events(event, GDK_ENTER_NOTIFY_MASK);
    g_signal_connect(G_OBJECT(event), "enter-notify-event", arg, NULL);
    
    if ( timer > 0 );
    //     g_timeout_add_seconds(timer, (GSourceFunc)*set, event);
    
    // Display the widget
    gtk_container_add(GTK_CONTAINER(event), img);
    if ( section == 1 )
        gtk_box_pack_end(GTK_BOX(bar), event, 0, 0, 5);
    
    // Display widgets
    gtk_widget_show(event);
    gtk_widget_show(img);
}
