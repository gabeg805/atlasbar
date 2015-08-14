/* *****************************************************************************
 * 
 * Name:    AtlasApp.h
 * Class:   <AtlasApp>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The tools to contruct a simple Atlas application.
 * 
 * Notes: Works well with Image and Label, try and generalize to other types.
 *        Try and wrap the StatusWidget functions into this.
 * 
 * *****************************************************************************
 */

/* Includes */




/* ******************************
 * ***** MERGE APPLICATIONS *****
 * ******************************
 */

// void AtlasApp::merge(AtlasApp &a)
// {
//     merge(a.widget);
// }

// void AtlasApp::merge(AtlasApp &a, enum AtlasAlign align)
// {
//     merge(a.widget, align);
// }

// void AtlasApp::merge(Gtk::Widget *w)
// {
//     if ( !dynamic_cast<Gtk::Container*>(widget) )
//         return;

//     size_t i;
//     for ( i = 0; i < size; ++i )
//         static_cast<Gtk::Container*>(&widget[i])->add(w[i]);
// }

// void AtlasApp::merge(Gtk::Widget *w, enum AtlasAlign align)
// {
//     if ( !dynamic_cast<Gtk::Container*>(widget) )
//         return;

//     size_t i;
//     switch ( align ) {
//     case ATLAS_ALIGN_LEFT:
//         for ( i = 0; i < size; ++i )
//             static_cast<Gtk::Box*>(&widget[i])->pack_start(w[i], Gtk::PACK_SHRINK);
//         return;
//     case ATLAS_ALIGN_CENTER:
//         for ( i = 0; i < size; ++i )
//             static_cast<Gtk::Box*>(&widget[i])->set_center_widget(w[i]);
//         return;
//     case ATLAS_ALIGN_RIGHT:
//         for ( i = 0; i < size; ++i )
//             static_cast<Gtk::Box*>(&widget[i])->pack_end(w[i], Gtk::PACK_SHRINK);
//         return;
//     }

// }
