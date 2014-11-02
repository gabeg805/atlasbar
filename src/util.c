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
// FUNCTIONS:
// 
//     get_gbar      - Get PID for running instances of GBAR
//     kill_gbar     - Kill running instances of GBAR
//     cleanup_child - Cleanup zombie processes
//     
//     widget_event  - Add events to widgets that are triggered with signals,
//                     i.e. Mouse hover, timers, etc.
// 
// 
// FILE STRUCTURE:
// 
//     * Includes and Declares
//     * Update Statusbar
//     * Add Events to Widgets
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
#include "../hdr/globals.h"
#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#define GBAR_LOG "/home/gabeg/.config/dwm/src/gbar/log/gbar.log"


// Declares
void setup_widget(GtkWidget *win, GtkWidget *widg, int pos[4]);
void file_write(char *file, char *opt, const char *fmt, ...);
char * file_read(char *file, int ln, int sz);
void kill_gbar();
void cleanup_child(int signal);
void widget_event(GtkWidget *holder, GtkWidget *widget, int timer, gboolean (*func)(gpointer));
void setup_window(GtkWidget *window, GtkWidget *bar);
void set_style();
void widget_mouse_enter(GtkWidget *win, GtkWidget *widget, int timer, gboolean (*func)(gpointer));

// Write to a file
void file_write(char *file, char *opt, const char *fmt, ...) {
    FILE *handle = fopen(file, opt);
    va_list args;
    
    va_start(args, fmt);
    vfprintf(handle, fmt, args);
    va_end(args);
    
    fclose(handle);
}


// Read a file's contents
char * file_read(char *file, int ln, int sz) {
    
    // Store file contents in variable
    FILE *handle = fopen(file, "r");
    char temp[sz];
    
    // Loop through file
    int i = 0;
    while (fgets(temp, sz, handle) != NULL ) {
        
        // Remove trailing newline characters
        char *pos;
        if ((pos=strchr(temp, '\n')) != NULL)
            *pos = '\0';
        
        // Break out of loop
        ++i;
        if ( i == ln )
            break;
    }
    
    // Close file
    fclose(handle);
    
    // Copy the line int to the return variable
    size_t len = strlen(temp) + 1;
    char *copy = malloc(len);
    assert(copy);
    snprintf(copy, len, "%s", temp);
    
    return copy;
}



// ////////////////////////////
// ///// UPDATE STATUSBAR /////
// ////////////////////////////

// Kill running instances of the gbar
void kill_gbar() {
    
    // Wait until file is created
    while ( access(GBAR_LOG, F_OK) != 0 ) {}
    int owner = atoi( file_read(GBAR_LOG, 1, 10) );
    
    // Command to search for running instances of gbar
    size_t len = 10;
    char *cmd = "pgrep gbar";
    FILE *handle = popen(cmd, "r");
    char proc[len];
    
    // Kill PID's that are found
    while ( fgets(proc, len, handle) != NULL ) {
        int pid = atoi(proc);
        if ( pid != owner ) {
            pid_t child = fork();
            if ( child == 0 ) {
                kill(pid, SIGHUP);
                exit(0);
            }
        }
    }
    
    // Close process
    pclose(handle);
}



// Cleanup zombie child processes
void cleanup_child(int signal) {
    wait(NULL);
}



// /////////////////////////////////
// ///// ADD EVENTS TO WIDGETS /////
// /////////////////////////////////

// Add events to widgets that are triggered with signals
void widget_event(GtkWidget *holder, GtkWidget *widget, int timer, gboolean (*func)(gpointer)) {
    
    // Initialize widgets
    GtkWidget *event = gtk_event_box_new();
    
    // Handle widget signals
    gtk_widget_add_events(event, GDK_ENTER_NOTIFY_MASK);
    g_signal_connect(G_OBJECT(event), "enter-notify-event", G_CALLBACK(func), NULL);
    
    if ( timer > 0 ) 
        g_timeout_add_seconds(timer, (GSourceFunc)*func, event);
        
    // Display the widget
    gtk_container_add(GTK_CONTAINER(event), widget);
    gtk_box_pack_end(GTK_BOX(holder), event, 0, 0, 0);
    
    gtk_widget_show(widget);
    gtk_widget_show(event);
}


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


// //////////////////////////////////
// ///// SETUP STATUSBAR WINDOW /////
// //////////////////////////////////

// Setup a widget
void setup_widget(GtkWidget *win, GtkWidget *widg, int pos[4]) {
    
    // Set window attributes
    gtk_window_move(GTK_WINDOW(win), pos[0], pos[1]);
    gtk_window_set_default_size(GTK_WINDOW(win), pos[2], pos[3]);
    gtk_widget_override_background_color(win, GTK_STATE_NORMAL, &color);
    
    // GTK signal
    if ( widg != NULL )
        gtk_container_add(GTK_CONTAINER(win), widg);
    g_signal_connect(win, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}


    
// Setup gbar root window
void setup_window(GtkWidget *window, GtkWidget *bar) {
        
    // Set window attributes
    gtk_window_move(GTK_WINDOW(window), 0, 0);
    gtk_window_set_default_size(GTK_WINDOW(window), screen_width, 20);
    gtk_widget_override_background_color(window, GTK_STATE_NORMAL, &color);
    
    // GTK signal
    gtk_container_add(GTK_CONTAINER(window), bar);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
}



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
