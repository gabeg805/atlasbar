/* *****************************************************************************
 * 
 * Name:    atlaswm.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The interface between the window manager and Atlas. The window
 *              manager catches key events and sends them through the interface,
 *              which then get converted into a format more readable for Atlas.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlaswm.h"
#include "atlasatom.h"
#include "atlasipc.h"
#include "atlaskeys.h"
#include "atlasutil.h"
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <X11/keysym.h>

/* Private functions */
static uint32_t wmdecode(uint32_t ui);

/* ************************************************************************** */
/* Execute Atlas initialization for window manager */
int wmatlasinit(uint32_t current, uint32_t ndesktop)
{
    /* Set atom values */
    setdefaultatomval("_NET_NUMBER_OF_DESKTOPS", (unsigned char*)&ndesktop);
    setdefaultatomval("_NET_CURRENT_DESKTOP", (unsigned char*)&current);

    /* Set up signal handling */
    signal(SIGHUP, wmcleanup);
    signal(SIGINT, wmcleanup);
    signal(SIGQUIT, wmcleanup);
    signal(SIGKILL, wmcleanup);

    /* Execute Atlas */
    pid_t pid = fork();
    if ( pid == 0 )
        return execl("/home/gabeg/scripts/programs/atlas/c++/atlas", "atlas",
                     NULL);
    int status;
    waitpid(pid, &status, WNOHANG);
    return 0;
}

/* ************************************************************************** */
/* Cleanup processes when termination signal received */
void wmcleanup(int signal)
{
    remove(getipcfile());
    /* remove(getlogfile()); */
    _exit(signal);
}

/* ************************************************************************** */
/* Send information from window manager to status bar */
void wmsendtoatlas(const Arg *arg)
{
    static int fd = -1;
    if ( (fd < 0) && ((fd=getipcfd(O_RDWR,0)) < 0) )
        return;
    if ( wripc(fd, wmdecode(arg->ui)) < 0 )
        return;

    uint16_t pid = pidof("atlas");
    if ( pid > 0 )
        kill(pid, SIGIO);
}

/* ************************************************************************** */
/* Decode information sent by window manager */
uint32_t wmdecode(uint32_t ui)
{
    uint32_t ret;
    if ( ui == ATLAS_KEY_BRT_UP )
        ret = ATLAS_SIG_BRT_UP;
    else if ( ui == ATLAS_KEY_BRT_DOWN )
        ret = ATLAS_SIG_BRT_DOWN;
    else if ( ui == ATLAS_KEY_VOL_DOWN )
        ret = ATLAS_SIG_VOL_DOWN;
    else if ( ui == ATLAS_KEY_VOL_MUTE )
        ret = ATLAS_SIG_VOL_MUTE;
    else if ( ui == ATLAS_KEY_VOL_UP )
        ret = ATLAS_SIG_VOL_UP;
    else if ( ui == ATLAS_KEY_VOL_PLAY )
        ret = ATLAS_SIG_VOL_PLAY;
    else if ( ui == ATLAS_KEY_VOL_NEXT )
        ret = ATLAS_SIG_VOL_NEXT;
    else if ( ui == ATLAS_KEY_VOL_PREV )
        ret = ATLAS_SIG_VOL_PREV;
    else {
        /* Determine number of desktops */
        static uint32_t num;
        getdefaultatomval("_NET_NUMBER_OF_DESKTOPS", (long*)&num);

        /* Update current desktop number */
        static uint32_t current;
        if ( (ui == XK_Left) || (ui == XK_Right) ) {
            getdefaultatomval("_NET_CURRENT_DESKTOP", (long*)&current);
            if ( ui == XK_Left ) {
                if ( ((int32_t)current-1) < 0 )
                    current = (num - 1);
                else
                    --current;
            }
            else if ( ui == XK_Right ) {
                if ( (current+1) >= num )
                    current = 0;
                else
                    ++current;
            }
            else
                ;
        }
        else
            current = logbase2(ui);
        ret = ATLAS_SIG_MON + current;
        setdefaultatomval("_NET_CURRENT_DESKTOP", (unsigned char*)&current);
    }

    return ret;
}
