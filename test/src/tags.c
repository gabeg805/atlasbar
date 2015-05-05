// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     tags.c
// 
// 
// SYNTAX: 
// 
//     #include "/PATH/TO/HEADER/tags.h"
// 
// 
// PURPOSE:
// 
//     Creates a tags widget on the main status bar that displays the tags in 
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
//     gabeg Nov 02 2014 <> Made it so that the tags widget did not have to rely on 
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
#include "../hdr/tags.h"
#include "../hdr/util.h"

#include <gtk/gtk.h>
#include <string.h>

// Declares
static int get_screen(int loc);

GdkRGBA color = {0.62, 0.62, 0.62, 1};
char *tags[]  = {"1", "2", "3", "4", "5", NULL};

static GtkWidget *tag_box[6];



// ////////////////////////////
// ///// SCREEN TAG INDEX /////
// ////////////////////////////

// Return the index of the screen tag
static int get_screen(int loc) {
    int i = 0;
    
    while ( loc != 0 ) {
        loc >>= 1;
        ++i;
    }
    
    return (i-1);
}



// ///////////////////////////////
// ///// DISPLAY TAGS WIDGET /////
// ///////////////////////////////

void set_tag(int loc) {
    
    GdkRGBA colorq  = {0.19, 0.19, 0.23, 1};
    int j = get_screen(loc);
    int i = 0;
    
    while ( tag_box[i] != NULL ) {
        // Extract widget from pointer
        GList *children  = gtk_container_get_children(GTK_CONTAINER(tag_box[i]));
        const gchar *str = gtk_label_get_text(GTK_LABEL(children->data));
        
        if ( strcmp(str, tags[j]) == 0 )
            gtk_widget_override_background_color(tag_box[i], GTK_STATE_NORMAL, &color);
        else 
            gtk_widget_override_background_color(tag_box[i], GTK_STATE_NORMAL, &colorq);
        
        // Free memory
        g_list_free(children);
        
        ++i;
    }
    
}


// Display the tags widget
void display_tags(int loc) {
    
    // Tag loop parameters
    /* GdkRGBA color = {0.62, 0.62, 0.62, 1}; */
    /* char *tags[]  = {"1", "2", "3", "4", "5", NULL}; */
    int padding   = 5;
    int i         = 0;
    
    // Create all tags
    while ( tags[i] != NULL ) {
        
        // Initialize tag widget
        GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        GtkWidget *tag = gtk_label_new(tags[i]);
        
        // Highlight current tag
        gtk_label_set_attributes(GTK_LABEL(tag), attrList);
        
        if ( i == get_screen(loc) ) 
            gtk_widget_override_background_color(box, GTK_STATE_NORMAL, &color);
        printf("AHHH: %s %d %s\n", gtk_label_get_text(GTK_LABEL(tag)), get_screen(loc), tags[i]);
        // Add tags to widget
        tag_box[i] = box;
        gtk_box_pack_start(GTK_BOX(box),    tag, 0, 0, padding);
        gtk_box_pack_start(GTK_BOX(App.holder), box, 0, 0, 0);
        
        // Display tags
        gtk_widget_show(tag);
        gtk_widget_show(box);
        
        ++i;
    }
    
    set_tag(loc);
}
