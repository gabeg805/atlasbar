// 
// CREATED BY: Gabriel Gonzalez (contact me at gabeg@bu.edu) 
// 
// 
// NAME:
// 
//     StatusWatcher.cc
// 
// 
// SYNTAX: 
// 
//     #include "StatusWatcher.h"
// 
// 
// PURPOSE:
// 
//     Catches the signals from the window manager that are emitted whenever a 
//     keypress that will change the statusbar is pressed. Upon receiving the signal,
//     this will send an update call the statusbar item that needs to be updated.
// 
// 
// MODIFICATION HISTORY:
// 	
//     gabeg May 02 2015 <> Created.
// 
//     gabeg May 07 2015 <> Finished converting the C implementation to C++.
// 
// **********************************************************************************



// /////////////////////////////////
// ///// INCLUDES AND DECLARES /////
// /////////////////////////////////

// Includes
#include "../hdr/StatusWatcher.h"
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
void statusWatcher(int sig) {
    
    // Retrieve value from semaphore
    int key;
    sem_t *sem = sem_open("/semi", O_RDONLY, 0644, key);
    
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
        
        brightness->widget->set();
        break;
    case 'P':
        if ( val == 0 )
            system("mocp -G");
        else if ( val == 1 )
            system("mocp -r");
        else if ( val == 2 )
            system("mocp -f");
        
        volume->widget->set();
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
        
        volume->widget->set();
        break;
    default:
        break;
    }
}
