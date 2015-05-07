// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     util.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/util.h"
// 
// 
// PURPOSE:
// 
//     Contains utility functions that each widget needs, this saves the trouble
//     of each widget source file having the same utility function, and 
//     centralizes it in one source file.
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg Sep 25 2014 <> created
// 
//     gabeg Oct 05 2014 <> Added a header to the source file and moved functions to 
//                          update the statusbar into this source file
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/util.h"
#include "../hdr/vol.h"
#include "../hdr/bright.h"
#include "../hdr/atlas.h"
#include "../hdr/tags.h"
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

// Declares
void cleanup_child(int signal);
void set_style();
void setup_widget(GtkWidget *win, GtkWidget *widg, int pos[4]);
void widget_mouse_enter(GtkWidget *win, GtkWidget *widget, int timer, gboolean (*func)(gpointer));
void widget_updater(int sig);



// ////////////////////////////
// ///// UPDATE STATUSBAR /////
// ////////////////////////////

// Cleanup zombie child processes
void cleanup_child(int signal) {
    wait(NULL);
}



// /////////////////////////////////
// ///// ADD EVENTS TO WIDGETS /////
// /////////////////////////////////

// Add events to widgets that are triggered with signals
void widget_mouse_enter(GtkWidget *win, GtkWidget *widget, int timer, gboolean (*func)(gpointer)) {
    
    // Initialize widgets
    GtkWidget *event = gtk_event_box_new();
    
    // Handle widget signals
    gtk_widget_add_events(event, GDK_ENTER_NOTIFY_MASK);
    g_signal_connect(G_OBJECT(event), "enter-notify-event", G_CALLBACK(func), NULL);
    
    if ( timer > 0 ) 
        g_timeout_add_seconds(timer, (GSourceFunc)*func, event);
        
    // Display the widget
    gtk_container_add(GTK_CONTAINER(event), widget);
    if ( win != NULL )
        gtk_container_add(GTK_CONTAINER(win), event);
        
    gtk_widget_show(event);
}


// ///////////////////////////////////
// ///// SETUP STATUSBAR WIDGETS /////
// ///////////////////////////////////

// Setup font attributes for text on the statusbar
void set_style() {
    
    // Define text attributes
    char *font = "Inconsolata";
    int fsize  = 8*1024;
    
    attrList = pango_attr_list_new();
    PangoAttribute *attrFont = pango_attr_family_new(font);
    PangoAttribute *attrSize = pango_attr_size_new(fsize);
    PangoAttribute *attrColor = pango_attr_foreground_new(65535, 65535, 65535);
    
    // Add attributes to the list (and increase the reference counter)
    attrList = pango_attr_list_ref(attrList);
    attrList = pango_attr_list_ref(attrList);
    pango_attr_list_insert(attrList, attrSize);
    pango_attr_list_insert(attrList, attrFont);
    pango_attr_list_insert(attrList, attrColor);
}



// Setup a widget
void setup_widget(GtkWidget *win, GtkWidget *widg, int pos[4]) {
    
    // Set window attributes
    GdkRGBA color = {0.19, 0.19, 0.23, 1};
    
    gtk_window_move(GTK_WINDOW(win), pos[0], pos[1]);
    gtk_window_set_default_size(GTK_WINDOW(win), pos[2], pos[3]);
    gtk_widget_override_background_color(win, GTK_STATE_NORMAL, &color);
    
    // GTK signal
    if ( widg != NULL )
        gtk_container_add(GTK_CONTAINER(win), widg);
    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}


void widget_updater(int sig) {
    int key, type, val;
    
    sem_t *sem = sem_open("/semi", O_RDONLY, 0644, key);
    /* FILE *handle = fopen("/home/gabeg/yuss", "a+"); */
    /* fprintf(handle, "Signal received\n"); */
    /* fclose(handle); */
    
    if ( sem == NULL )
        return;
    
    sem_getvalue(sem, &key);
    
    type = (key >> 8);
    val  = (key & 0xFF);
    
    /* handle = fopen("/home/gabeg/yuss", "a+"); */
    /* fprintf(handle, "Key = 0x%x\n", key); */
    /* fprintf(handle, "Type = 0x%x\n", type); */
    /* fprintf(handle, "Val = 0x%x\n", val); */
    /* fclose(handle); */
    
    switch ( type ) {
    case 'B':
        if ( val == 0 )
            system("xbacklight -inc 10");
        else if ( val == 1 )
            system("xbacklight -dec 10");
        
        display_brightness();
        break;
    case 'P':
        if ( val == 0 )
            system("mocp -G");
        else if ( val == 1 )
            system("mocp -r");
        else if ( val == 2 )
            system("mocp -f");
        
        display_volume();
        break;
    case 'T':
        val = (key & 0xFF);
        display_tags(val);
        break;
    case 'V':
        if ( val == 0 )
            system("amixer -q set Master 5%+");
        else if ( val == 1 )
            system("amixer -q set Master 5%-");
        else if ( val == 2 )
            system("amixer -q set Master toggle");
        
        display_volume();
        break;
    default:
        break;
    }
}
