/* *****************************************************************************
 * 
 * Name:    atlaswm.h
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas Window Manager. This will interface with a window
 *              manager (WM), default is 'dwm', so that Atlas can catch key
 *              events. Normally, whichever toplevel window is in focus will
 *              capture key events. In this case, the WM is the toplevel window,
 *              as Atlas is not toplevel, and so the WM will be capturing key
 *              events intended for Atlas. To ameliorate this, an interface is
 *              needed to bridge the two.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

#ifndef ATLAS_WM_H
#define ATLAS_WM_H

#include <stdint.h>

void     barsignal(void *dwmarg);
uint32_t barkey(uint32_t ui);


#endif /* ATLAS_WM_H */

/* /\* Includes *\/ */
/* #include "/home/gabeg/scripts/programs/atlas/c++/include/AtlasSignalType.h" */
/* #include "/home/gabeg/scripts/programs/atlas/c++/include/atlasipc.h" */
/* #include <fcntl.h> */
/* #include <signal.h> */
/* /\* #include <semaphore.h> *\/ */
/* #include <stdint.h> */
/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <string.h> */
/* #include <sys/stat.h> */
/* #include <sys/types.h> */

/* /\* Defines *\/ */

/* /\* Declares *\/ */
/* void     barsignal(const Arg *arg); */
/* uint32_t  barkey(uint32_t ui); */
/* uint32_t logbase2(uint32_t val); */
/* uint16_t pidof(char *prog); */

/* /\* Globals *\/ */
/* /\* unsigned int statusBarScreen = 1; *\/ */

/* #include <fcntl.h> */
/* #include <unistd.h> */

/* /\* ************************************************************************** *\/ */
/* /\* *\/ */
/* void barsignal(const Arg *arg) */
/* { */
/*     wrpipe(arg->ui); */

/*     /\* int fd = open("/tmp/atlas", O_RDONLY); *\/ */
/*     /\* if ( fd < 0 ) *\/ */
/*     /\*     return; *\/ */
/*     /\* int wr = write(fd, &arg->ui, sizeof(arg->ui)); *\/ */
/*     /\* if ( wr < 0 ) *\/ */
/*     /\*     return; *\/ */
/*     /\* int cl = close(fd); *\/ */
/*     /\* if ( cl < 0 ) *\/ */
/*     /\*     return; *\/ */

/*     /\* uint16_t pid = pidof("atlas"); *\/ */
/*     /\* if ( pid > 0 ) { *\/ */
/*     /\*     sem_unlink("/semi"); *\/ */
/*     /\*     sem_t *sem = sem_open("/semi", O_CREAT, 0644, arg->ui); *\/ */
/*     /\*     sem_close(sem); *\/ */
/*     /\*     kill(pid, SIGUSR1); *\/ */
/*     /\* } *\/ */
/* } */

/* /\* ************************************************************************** *\/ */
/* /\* Split this function up into two */
/*  * Put other half in barsignal */
/*  * if arg->ui > ATLAS_SIG_MAX then vol/brt key *\/ */
/* uint32_t barkey(uint32_t ui) */
/* { */
/*     static uint32_t screen = 1; */
/*     int max = 1 << (5-1); */
/*     uint32_t ret; */

/*     FILE *fp = fopen("/home/gabeg/.config/dwm/stuff.txt", "a+"); */
/*     fprintf(fp, "key: 0x%0x | screen: 0x%0x 0x%0x | max: 0x%0x\n", */
/*             ui, screen, logbase2(screen), max); */

/*     if ( ui == XK_Left ) { */
/*         if ( (screen >>= 1) == 0 ) */
/*             screen = max; */
/*         ret    = ATLAS_SIG_MON + logbase2(screen); */
/*         fprintf(fp, "left: 0x%0x \n", screen); */
/*     } */
/*     else if ( ui == XK_Right ) { */
/*         if ( (screen <<= 1) > max ) */
/*             screen = 1; */
/*         ret    = ATLAS_SIG_MON + logbase2(screen); */
/*         fprintf(fp, "right: 0x%0x\n", screen); */
/*     } */
/*     else if ( ui == ATLAS_KEY_BRT_UP ) */
/*         ret = ATLAS_SIG_BRT_UP; */
/*     else if ( ui == ATLAS_KEY_BRT_DOWN ) */
/*         ret = ATLAS_SIG_BRT_DOWN; */
/*     else if ( ui == ATLAS_KEY_VOL_DOWN ) */
/*         ret = ATLAS_SIG_VOL_DOWN; */
/*     else if ( ui == ATLAS_KEY_VOL_MUTE ) */
/*         ret = ATLAS_SIG_VOL_MUTE; */
/*     else if ( ui == ATLAS_KEY_VOL_UP ) */
/*         ret = ATLAS_SIG_VOL_UP; */
/*     else if ( ui == ATLAS_KEY_VOL_PLAY ) */
/*         ret = ATLAS_SIG_VOL_PLAY; */
/*     else if ( ui == ATLAS_KEY_VOL_NEXT ) */
/*         ret = ATLAS_SIG_VOL_NEXT; */
/*     else if ( ui == ATLAS_KEY_VOL_PREV ) */
/*         ret = ATLAS_SIG_VOL_PREV; */
/*     else { */
/*         screen = 1 << logbase2(ui); */
/*         ret    = ATLAS_SIG_MON + logbase2(screen); */
/*     } */

/*     fprintf(fp, "ret: 0x%0x\n\n", ret); */
/*     fclose(fp); */

/*     return ret; */
/* } */

/* /\* ************************************************************************** *\/ */
/* /\* Return the log base 2 of the value*\/ */
/* uint32_t logbase2(uint32_t val) */
/* { */
    
/*     uint32_t i; */
/*     for ( i = 0; i < 31; ++i ) */
/*         if ( (val >>= 1) == 0 ) */
/*             return i; */
/*     return i; */
/* } */

/* /\* /\\* ************************************************************************** *\\/ *\/ */
/* /\* /\\* Check if a program is running *\\/ *\/ */
/* /\* uint16_t pidof(char *prog) *\/ */
/* /\* { *\/ */
/* /\*     static char  output[256]; *\/ */
/* /\*     static char  cmd[256]; *\/ */
/* /\*     size_t       len = strlen(prog); *\/ */
/* /\*     if ( len > (sizeof(cmd)-6) ) *\/ */
/* /\*         return 0; *\/ */
/* /\*     strcpy(cmd, (char*)"pidof "); *\/ */
/* /\*     strncat(cmd, prog, len); *\/ */
/* /\*     FILE *stream = popen(cmd, "r"); *\/ */
/* /\*     fgets(output, sizeof(output), stream); *\/ */
/* /\*     pid_t pid = strtoul(output, NULL, 10); *\/ */
/* /\*     pclose(stream); *\/ */
/* /\*     return pid; *\/ */
/* /\* } *\/ */
