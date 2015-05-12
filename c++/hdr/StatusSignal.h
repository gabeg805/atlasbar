// -*-c++-*-
// **********************************************************************************
// 
// Name:    StatusSignal.h
// Class:   <StatusSignal>
// Author:  Gabriel Gonzalez
// Email:   gabeg@bu.edu
// License: The MIT License (MIT)
// 
// Description: Catches signals that are sent from the window manager, and executes
//              tasks based on the signal.
//              
// Notes: None.
// 
// **********************************************************************************


// ============
// Header Guard
// ============

#ifndef STATUSSIGNAL_H
#define STATUSSIGNAL_H


// ======
// Public
// ======

#include "../hdr/Volume.h"
#include "../hdr/Brightness.h"
#include "../hdr/Workspace.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <cstdlib>



// //////////////////////////////////////////
// ///// WATCH FOR STATUSBAR KEYPRESSES /////
// //////////////////////////////////////////

// Waits for a signal from the window manager when specific keys that will 
// change the statusbar are pressed 

class StatusSignal {
 public:
    
    static void statusSigCatcher(int sig) {
        
        // Retrieve value from semaphore
        int key;
        sem_t* sem = sem_open("/semi", O_RDONLY, 0644, key);
    
        if ( sem == NULL )
            return;
        else
            sem_getvalue(sem, &key);
        
        // Update statusbar and call application command
        int type = (key >> 8);
        int val  = (key & 0xFF);
        
        switch ( type ) {
        case 'B':
            if ( val == 0 )
                system("xbacklight -inc 10");
            else if ( val == 1 )
                system("xbacklight -dec 10");
            
            brightness->widget->set <Gtk::Image> ();
            break;
        case 'P':
            if ( val == 0 )
                system("mocp -G");
            else if ( val == 1 )
                system("mocp -r");
            else if ( val == 2 )
                system("mocp -f");
                        
            volume->widget->set <Gtk::Image> ();
            break;
        case 'T':
            val = (key & 0xFF);
            
            workspace->widget->set(val);
            break;
        case 'V':
            if ( val == 0 )
                system("amixer -q set Master 5%+");
            else if ( val == 1 )
                system("amixer -q set Master 5%-");
            else if ( val == 2 )
                system("amixer -q set Master toggle");
            
            volume->widget->set <Gtk::Image> ();
            break;
        default:
            break;
        }
    }
};

#endif
