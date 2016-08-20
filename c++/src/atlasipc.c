/* *****************************************************************************
 * 
 * Name:    atlasipc.c
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The interprocess communication method between Atlas and the
 *              system window manager.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlasipc.h"
#include "atlasmem.h"
#include "atlasutil.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* ************************************************************************** */
/* Setup IPC */
int setupipc(void)
{
    /* Open IPC file */
    int fd;
    if ( (fd=openipc()) < 0 )
        return -1;
    /* Lock IPC file */
    if ( flock(fd, LOCK_EX) < 0 )
        return -1;
    /* Memory map IPC file */
    if ( memmap(fd) < 0 )
        return -1;
    return fd;
}

/* ************************************************************************** */
/* Open IPC file */
int openipc(void)
{
    static mode_t  mode  = 0644;
    static int     flags = O_RDWR;
    static int     fd    = -1;
    const char    *file  = getipcfile();

    /* File descriptor already opened */
    if ( fd > 0 )
        return fd;
    /* IPC file exists */
    if ( access(file, F_OK) == 0 ) {
        if ( (fd=open(file,flags)) < 0 )
            remove(file);
    }
    /* Create IPC file */
    else
        fd = open(file,flags|O_CREAT, mode);

    return fd;
}

/* ************************************************************************** */
/* Read IPC data */
int32_t readipc(int fd)
{
    uint32_t buf;
    if ( lseek(fd, 0, SEEK_SET) < 0 )
        return -1;
    if ( read(fd, &buf, sizeof(buf)) <= 0 )
        return -1;
    if ( lseek(fd, 0, SEEK_SET) < 0 )
        return -1;
    return buf;
}

/* ************************************************************************** */
/* Write to the pipe */
int32_t writeipc(int fd, uint32_t buf)
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
/* Return IPC file */
const char * getipcfile(void)
{
    return "/dev/shm/atlas-shm";
}
