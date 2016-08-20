/* *****************************************************************************
 * 
 * Name:    atlasmem.c
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas method for managing shared memory between it and the
 *              system window manager.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Includes */
#include "atlasmem.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>

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
