// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     date.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/date.h"
// 
// 
// PURPOSE:
// 
//     Creates a date widget on the main status bar that displays the date in 
//     the format: "Sun Oct 5, 12:48 PM".
// 
// 
// KEYWORDS:
// 
//     N/A
// 
// 
// FUNCTIONS:
// 
//     set_date_label - Determine the date and set the date on the widget
//     
//     display_date   - Display the date widget
// 
// 
// FILE STRUCTURE:
// 
//     * Set Date Label
//     * Display Date Widget
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg Sep 15 2014 <> created
// 
//     gabeg Oct 05 2014 <> Added a header to the source file.
// 
//     gabeg Nov 02 2014 <> Made it so that the date widget did not have to rely on 
//                          the Atlas frame (being passed in as a parameter). 
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/date.h"
#include "../hdr/atlas.h"
#include "../hdr/util.h"
#include <gtk/gtk.h>
#include <time.h>

#define   XPOS              640
#define   YPOS              0


// Declares
static gboolean set_date_label(gpointer data);



// //////////////////////////
// ///// SET DATE LABEL /////
// //////////////////////////

// Set the label for the date widget
static gboolean set_date_label(gpointer data) {
    
    // Define date widget
    GtkWidget *date = (GtkWidget *) data;
    
    // Obtain current time as seconds elapsed since the Epoch.
    time_t current_time = time(NULL);
    char time_string[50];
    struct tm *tmp;
    
    // Convert time
    char *fmt  = "%a %b %-d, %-I:%M %p";
    tmp = localtime(&current_time);
    strftime(time_string, sizeof(time_string), fmt, tmp);
    
    // Set the label text and font
    gtk_label_set_attributes(GTK_LABEL(date), attrList);
    gtk_label_set_text(GTK_LABEL(date), time_string);
    
    return TRUE;
}



// ///////////////////////////////
// ///// DISPLAY DATE WIDGET /////
// ///////////////////////////////

// Display the date widget
void display_date() {
    
    // Setup the date widget
    GtkWidget *win  = gtk_window_new(GTK_WINDOW_POPUP);
    GtkWidget *date = gtk_label_new("");
    set_date_label(date);
    
    // Setup widget
    int pos[4] = {XPOS, YPOS, 0, 20};
    setup_widget(win, date, pos);
    g_timeout_add_seconds(60, set_date_label, date);
    
    // Display widgets
    gtk_widget_show(date);
    gtk_widget_show(win);
}
