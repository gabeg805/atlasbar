/* *****************************************************************************
 * 
 * Name:    atlaswm.h
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

/* Header guard */
#ifndef ATLAS_WM_H
#define ATLAS_WM_H

/* C++ to C guard */
#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
#include <stdint.h>

/* Types */
#ifndef DWM
typedef union {
	int i;
	unsigned int ui;
	float f;
	const void *v;
} Arg;
#endif

/* Public functions */
int  wmatlasinit(uint32_t current, uint32_t ndesktop);
void wmcleanup(int signal);
void wmsendtoatlas(const Arg *arg);

#ifdef __cplusplus
}
#endif

#endif /* ATLAS_WM_H */
