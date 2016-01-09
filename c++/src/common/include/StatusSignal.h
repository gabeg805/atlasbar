/* *****************************************************************************
 * 
 * Name:    StatusSignal.h
 * Class:   <StatusSignal>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: Catches signals that are sent from the window manager, and executes
 *              tasks based on the signal.
 *              
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header Guard */
#ifndef STATUSSIGNAL_H
#define STATUSSIGNAL_H

/* Includes */
#include "AtlasSignalType.h"
/* #include "Volume.h" */
/* #include "Brightness.h" */
/* #include "Workspace.h" */
#include <stdint.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <cstdlib>

/* ******************************************
 * ***** WATCH FOR STATUSBAR KEYPRESSES *****
 * ******************************************
 */

/* Waits for a signal from the window manager when specific keys that will 
 * change the statusbar are pressed */
class StatusSignal {
public:

    static void statusSigCatcher(int sig)
    {
        /* Retrieve value from semaphore */
        unsigned int key;
        unsigned int val;
        sem_t* sem = sem_open("/semi", O_RDONLY, 0644, 0);

        if ( sem == NULL )
            return;
        else
            sem_getvalue(sem, (int*)&key);

        FILE *fp = fopen("/home/gabeg/.config/dwm/stuff.txt", "a+");
        fprintf(fp, "sig: 0x%0x\n", key);

        // Update statusbar and call application command
        switch ( key ) {
        case AtlasSignal::BRIGHT_UP:
            system("xbacklight -inc 10");
            brightness.update(brightness.widget);
            break;
        case AtlasSignal::BRIGHT_DOWN:
            system("xbacklight -dec 10");
            brightness.update(brightness.widget);
            break;
        case AtlasSignal::TRACK_PLAY:
            system("mocp -G");
            volume.update(volume.widget);
            break;
        case AtlasSignal::TRACK_NEXT:
            system("mocp -f");
            volume.update(volume.widget);
            break;
        case AtlasSignal::TRACK_PREV:
            system("mocp -r");
            volume.update(volume.widget);
            break;
        case AtlasSignal::VOL_UP:
            system("amixer -q set Master 5%+");
            volume.update(volume.widget);
            break;
        case AtlasSignal::VOL_DOWN:
            system("amixer -q set Master 5%-");
            volume.update(volume.widget);
            break;
        case AtlasSignal::VOL_MUTE:
            system("amixer -q set Master toggle");
            volume.update(volume.widget);
            break;
        default:
            if ( (key & 0xf0) == AtlasSignal::SCREEN ) {
                val = (key & 0xf);
                fprintf(fp, "val 0x%0x\n", val);
                workspace.screen = val;
                workspace.update(workspace.widget);
            }
            break;
        }
        fclose(fp);
    }
};

#endif
