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
// #include "../hdr/StatusBar.h"
#include "../hdr/util.h"
#include "../hdr/Volume.h"
#include "../hdr/Brightness.h"
#include "../hdr/Workspace.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

#include <iostream>
#include <string>

using namespace std;


// ///////////////////////////////////
// ///// SETUP STATUSBAR WIDGETS /////
// ///////////////////////////////////


void widget_updater(int sig) {
    
    int key, type, val;
    sem_t *sem = sem_open("/semi", O_RDONLY, 0644, key);
    
    if ( sem == NULL )
        return;
    
    sem_getvalue(sem, &key);
    
    type = (key >> 8);
    val  = (key & 0xFF);
    
    switch ( type ) {
    case 'B':
        if ( val == 0 )
            system("xbacklight -inc 10");
        else if ( val == 1 )
            system("xbacklight -dec 10");
        
        // Make barimage static
        // if ( brightness->widget.icon == 0 )
        //     cout << "Fuck" << endl;
        
        brightness->set();
        break;
    case 'P':
        if ( val == 0 )
            system("mocp -G");
        else if ( val == 1 )
            system("mocp -r");
        else if ( val == 2 )
            system("mocp -f");
        
        volume->set();
        break;
    case 'T':
        val = (key & 0xFF);
        
        // set_tag(val);
        break;
    case 'V':
        if ( val == 0 )
            system("amixer -q set Master 5%+");
        else if ( val == 1 )
            system("amixer -q set Master 5%-");
        else if ( val == 2 )
            system("amixer -q set Master toggle");
        
        volume->set();
        break;
    default:
        break;
    }
}



// Return current brightness level
int get_percent(std::string cmd) {
    
    // Get output from command
    FILE *handle = popen(cmd.c_str(), "r");
    char output[20];
    fgets(output, sizeof(output), handle);    
    fclose(handle);
    
    // Convert command output to integer volume level
    int i = 0;
    int j = 0;
    char level[4];
    memset(level, 0, sizeof(level));
    
    while ( (output[i] != 0) && (j != (sizeof(level)-1)) ) {
        if ( (output[i] >= '0') && (output[i] <= '9') ) {
            level[j] = output[i];
            if ( atoi(level) > 100 )
                level[j] = '\0';
            ++j;
        }
        
        ++i;
    }
    
    return atoi(level);
}
