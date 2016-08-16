/* *****************************************************************************
 * 
 * Name:    atlasipc.h
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

/* Header guard */
#ifndef ATLAS_IPC_H
#define ATLAS_IPC_H

/* C++ to C guard */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stdint.h>
#include <sys/types.h>

/* Public functions */
int     initipc(void);
int32_t rdipc(int fd);
int32_t wripc(int fd, uint32_t buf);
int     memmap(int fd);
int     memunmap(long *addr);
int     getipcfd(int flags, mode_t mode);

#ifdef __cplusplus
}
#endif

#endif /* ATLAS_IPC_H */
