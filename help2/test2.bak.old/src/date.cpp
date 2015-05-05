// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     date.cpp
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
// MODIFICATION HISTORY:
// 	
//     gabeg Sep 15 2014 <> created
// 
//     gabeg Oct 05 2014 <> Added a header to the source file.
// 
//     gabeg Nov 02 2014 <> Made it so that the date widget did not have to rely on 
//                          the Atlas frame (being passed in as a parameter). 
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
#include "../hdr/date.h"
#include "../hdr/util.h"

#include <gtk/gtk.h>
#include <time.h>

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
    char fmt[]  = "%a %b %-d, %-I:%M %p";
    tmp = localtime(&current_time);
    strftime(time_string, sizeof(time_string), fmt, tmp);
    
    // Set the label text and font
    gtk_label_set_attributes(GTK_LABEL(date), Atlas.attr);
    gtk_label_set_text(GTK_LABEL(date), time_string);
    
    return TRUE;
}



// ///////////////////////////////
// ///// DISPLAY DATE WIDGET /////
// ///////////////////////////////

// Display the date widget
void display_date() {
    
    // Setup the date widget
    GtkWidget *date = gtk_label_new("");
    set_date_label(date);
    
    // Setup widget
    g_timeout_add_seconds(60, set_date_label, date);
    gtk_box_set_center_widget(GTK_BOX(Atlas.bar), date);
    
    // Display widgets
    gtk_widget_show(date);
}
