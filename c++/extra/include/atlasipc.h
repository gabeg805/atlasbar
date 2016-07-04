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

/* Header guard */
#ifndef ATLAS_IPC_H
#define ATLAS_IPC_H

/* Includes */
#include <stdint.h>
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Types */
#ifndef DWM
typedef union {
	int i;
	unsigned int ui;
	float f;
	const void *v;
} Arg;
#endif

int          initipc(void);
int32_t      rdipc(int fd);
int32_t      wripc(int fd, uint32_t buf);
int          memmap(int fd);
int          memunmap(long *addr);
int          getipcfd(int flags, mode_t mode);
void         barsignal(const Arg *arg);

extern uint32_t DWMSCREEN;

#ifdef __cplusplus
}
#endif

#endif /* ATLAS_IPC_H */
