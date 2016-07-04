/* *****************************************************************************
 * 
 * Name:    Statusbar.cc
 * Class:   <Statusbar>
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas status bar - contains all status bar applications.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "../include/atlasipc.h"
#include "../include/AtlasSignalType.h"
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <X11/keysym.h>


/* Globals */
uint32_t           DWMSCREEN = 1;
static const char *IPCFILE   = "/tmp/atlasmap";

/* ************************************************************************** */
/* Initialize the IPC pipe */
int initipc(void)
{
    static mode_t      mode  = 0644;
    static int         flags = O_RDWR;
    static int         fd    = -1;

    if ( fd != -1 )
        return fd;
    if ( access(IPCFILE, F_OK) == 0 ) {
        if ( (fd=getipcfd(flags,0)) < 0 ) {
            remove(IPCFILE);
            return fd;
        }
    }
    else
        if ( (fd=getipcfd((flags|O_CREAT), mode)) < 0 )
            return fd;
    if ( flock(fd, LOCK_EX) < 0 )
        return -1;
    if ( memmap(fd) < 0 )
        return -1;

    /* wripc(fd, 0); */
    return fd;
}

/* ************************************************************************** */
/* Read from the pipe */
int32_t rdipc(int fd)
{
    uint32_t buf;
    if ( lseek(fd, 0, SEEK_SET) < 0 )
        return -1;
    if ( read(fd, &buf, sizeof(buf)) < 0 )
        return -1;
    if ( lseek(fd, 0, SEEK_SET) < 0 )
        return -1;
    return buf;
}

/* ************************************************************************** */
/* Write to the pipe */
int32_t wripc(int fd, uint32_t buf)
{
    int32_t ret;
    if ( lseek(fd, 0, SEEK_SET) < 0 )
        return -1;
    if ( (ret=write(fd, &buf, sizeof(buf))) < 0 )
        return -1;
    if ( lseek(fd, 0, SEEK_SET) < 0 )
        return -1;
    return ret;
}

/* ************************************************************************** */
/* Create a memory mapped region for ICP */
int memmap(int fd)
{
    static long   *addr  = NULL;
    static size_t  size  = sizeof(uint32_t);
    static int     prot  = (PROT_READ | PROT_WRITE);
    static int     flags = MAP_SHARED;

    if ( addr != NULL )
        return 0;
    if ( (addr=(long *)mmap(NULL, size, prot, flags, fd, 0)) == MAP_FAILED )
        return -1;
    return 0;
}

/* ************************************************************************** */
/* Unmap the shared memory region */
int memunmap(long *addr)
{
    if ( addr == NULL )
        return -1;
    if ( munmap(addr, sizeof(uint32_t)) < 0 )
        ;
    return 0;
}

/* ************************************************************************** */
/* Initialize the IPC pipe */
int getipcfd(int flags, mode_t mode)
{
    return (mode == 0) ? open(IPCFILE, flags) : open(IPCFILE, flags, mode);
}

/* ************************************************************************** */
uint32_t logbase2(uint32_t val)
{
    uint32_t i;
    for ( i = 0; i < 31; ++i )
        if ( (val >>= 1) == 0 )
            return i;
    return i;
}

/* This causes an error when prog is ctrl+c'ed due to static mem */
uint16_t pidof(const char *prog)
{
    const char    *parent  = "/proc";
    DIR           *dstream = opendir(parent);
    FILE          *fstream;
    struct dirent *dir;
    struct stat    info;
    static char    path[256];
    static char    line[256];
    char          *ret;
    size_t         len;
    while ( (dir=readdir(dstream)) != NULL ) {
        if ( dir->d_type == DT_DIR ) {
            len = 5+1+strlen(dir->d_name)+8+1;
            if ( sizeof(path) < len )
                continue;
            snprintf(path, len, "%s/%s/cmdline", parent, dir->d_name);
            if ( stat(path, &info) != 0 )
                continue;
            if ( getuid() != info.st_uid )
                continue;
            fstream = fopen(path, "r");
            ret     = fgets(line, sizeof(line), fstream);
            fclose(fstream);
            if ( ret == NULL )
                continue;
            if ( strstr(line, prog) != NULL )
                return strtoul(dir->d_name, NULL, 10);
        }
    }

    return 0;
}

/* ************************************************************************** */
/* */
uint32_t barkey(uint32_t ui)
{
    uint32_t num = 5;
    uint32_t max = 1 << (num-1);
    uint32_t ret;

    FILE *fp = fopen("/home/gabeg/.config/dwm/stuff.txt", "a+");
    fprintf(fp, "key: 0x%0x | screen: 0x%0x 0x%0x | max: 0x%0x\n",
            ui, DWMSCREEN, logbase2(DWMSCREEN), max);

    if ( ui == XK_Left ) {
        if ( (DWMSCREEN>>=1) == 0 )
            DWMSCREEN = max;
        ret = ATLAS_SIG_MON + logbase2(DWMSCREEN);
        fprintf(fp, "left: 0x%0x \n", DWMSCREEN);
    }
    else if ( ui == XK_Right ) {
        if ( (DWMSCREEN<<=1) > max )
            DWMSCREEN = 1;
        ret = ATLAS_SIG_MON + logbase2(DWMSCREEN);
        fprintf(fp, "right: 0x%0x\n", DWMSCREEN);
    }
    else if ( ui == ATLAS_KEY_BRT_UP )
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
        DWMSCREEN = 1 << logbase2(ui);
        ret    = ATLAS_SIG_MON + logbase2(DWMSCREEN);
    }

    fprintf(fp, "ret: 0x%0x\n\n", ret);
    fclose(fp);

    return ret;
}

void barsignal(const Arg *arg)
{
    FILE *handle = fopen("/home/gabeg/.config/dwm/view.txt", "a+");
    fprintf(handle, "barsignal\n");
    static int fd = -1;
    if ( (fd < 0) && ((fd=getipcfd(O_RDWR,0)) < 0) ) {
        fprintf(handle, "Bad fd: %d\n", fd);
        fclose(handle);
        return;
    }
    fprintf(handle, "fd: %d | wr: 0x%x\n", fd, arg->ui);
    if ( wripc(fd, barkey(arg->ui)) < 0 ) {
        fprintf(handle, "write error\n");
        fclose(handle);
        return;
    }

    uint16_t pid = pidof("atlas");
    fprintf(handle, "pid: %u\n", pid);
    if ( pid > 0 )
        kill(pid, SIGIO);
    fclose(handle);
}
