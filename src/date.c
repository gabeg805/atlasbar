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
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/date.h"
#include <gtk/gtk.h>

// Declares
gboolean set_date_label(gpointer data);
void display_date(GtkWidget *bar, PangoAttrList *attrList);

PangoAttrList *STYLE;



// //////////////////////////
// ///// SET DATE LABEL /////
// //////////////////////////

// Set the label for the date widget
gboolean set_date_label(gpointer data) {
    
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
    gtk_label_set_attributes(GTK_LABEL(date), STYLE);
    gtk_label_set_text(GTK_LABEL(date), time_string);
    
    return TRUE;
}



// ///////////////////////////////
// ///// DISPLAY DATE WIDGET /////
// ///////////////////////////////

// Display the date widget
void display_date(GtkWidget *bar, PangoAttrList *attrList) {
    
    // Setup the date widget
    GtkWidget *date = gtk_label_new("");
    STYLE = attrList;
    set_date_label(date);
    
    // Put it on the main bar gui 
    g_timeout_add_seconds(60, set_date_label, date);
    gtk_box_set_center_widget(GTK_BOX(bar), date);
        
    // Displat the date widget
    gtk_widget_show(date);
}
