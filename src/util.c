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
#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Declares
int get_gbar();
void kill_gbar();
void cleanup_child(int signal);
void widget_event(GtkWidget *holder, GtkWidget *widget, int timer, gboolean (*func)(gpointer));



// ////////////////////////////
// ///// UPDATE STATUSBAR /////
// ////////////////////////////

// Return PID of running instances of the gbar
int get_gbar() {
    
    // Command to search for running instances of gbar
    size_t sz = 50;
    char cmd[sz];
    snprintf(cmd, sz, "%s | %s %d | %s", "pgrep gbar", "grep -v", getpid(), "head -1");
    
    // Return process id from command
    char proc[sizeof(long long)];
    FILE *handle = popen(cmd, "r");
    fgets(proc, sizeof(long long), handle);
    pclose(handle);
    
    return atoi(proc);
}



// Kill running instances of the gbar
void kill_gbar() {
    int pro = get_gbar();
    if ( pro != 0 ) {
        int pid = fork();
        if ( pid == 0 ) {
            kill(pro, SIGHUP);
            exit(0);
        }
    }
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
