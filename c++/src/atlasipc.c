/* *****************************************************************************
 * 
 * Name:    atlasipc.cc
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The interprocess communication method between Atlas and the
*               system window manager.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlasipc.h"
#include <stdio.h>
#include <sys/file.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

/* ************************************************************************** */
/* Initialize the IPC pipe */
int initipc(void)
{
    static mode_t mode  = 0644;
    static int    flags = O_RDWR;
    static int    fd    = -1;

    if ( fd != -1 )
        return fd;
    if ( access(getipcfile(), F_OK) == 0 ) {
        if ( (fd=getipcfd(flags,0)) < 0 ) {
            remove(getipcfile());
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
    return (mode == 0) ? open(getipcfile(), flags) : open(getipcfile(), flags,
                                                          mode);
}

/* ************************************************************************** */
/* Return IPC file */
const char * getipcfile(void)
{
    return "/dev/shm/atlas-shm";
}
