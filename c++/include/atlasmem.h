/* *****************************************************************************
 * 
 * Name:    atlasmem.h
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

/* Header guard */
#ifndef ATLAS_MEM_H
#define ATLAS_MEM_H

/* C++ to C guard */
#ifdef __cplusplus
extern "C" {
#endif

/* Public functions */
int memmap(int fd);
int memunmap(long *addr);

#ifdef __cplusplus
}
#endif

#endif /* ATLAS_MEM_H */
