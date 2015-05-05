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
#include "../hdr/StatusBar.h"
#include "../hdr/date.h"
// #include "../hdr/util.h"

// #include <gtk/gtk.h>
#include <gtkmm.h>
#include <time.h>

#include <sstream>
#include <string>

#include <ctime>
#include <iostream>
// using namespace std;

// Declares
// static gboolean set_date_label(gpointer data);



// //////////////////////////
// ///// SET DATE LABEL /////
// //////////////////////////

// Set the label for the date widget
std::string nowsers() {
    
    // Setup time struct
    std::string fmt = "%a %b %-d, %-I:%M:%S %p";
    time_t t        = time(0);
    struct tm * now = localtime(&t);
    
    // Convert time struct to readable format
    char time_string[30];
    strftime(time_string, sizeof(time_string), fmt.c_str(), now);
    
    std::cout << time_string << std::endl;
    
    return std::string(time_string);
}



// ///////////////////////////////
// ///// DISPLAY DATE WIDGET /////
// ///////////////////////////////

// Display the date widget
void display_date(Gtk::Box *ats) {
    
    BarLabel label(ats, nowsers);
    
    // Glib::signal_timeout().connect_seconds(sigc::mem_fun(label, &BarLabel::incr), 1);
    
    // // Setup the date widget
    // GtkWidget *date = gtk_label_new("");
    // set_date_label(date);
    
    // // Setup widget
    // g_timeout_add_seconds(60, set_date_label, date);
    // gtk_box_set_center_widget(GTK_BOX(Atlas.bar), date);
    
    // // Display widgets
    // gtk_widget_show(date);
}
