/* *****************************************************************************
 * 
 * Name:    atlasatom.h
 * Author:  Gabriel Gonzalez
 * Email:   gabeg@bu.edu
 * License: The MIT License (MIT)
 * 
 * Description: The Atlas atom handler.
 * 
 * Notes: None.
 * 
 * *****************************************************************************
 */

/* Header guard */
#ifndef ATLAS_ATOM_H
#define ATLAS_ATOM_H

/* Includes */
#include <stdbool.h>
#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Public functions */
long      getatomval(Display *display, Window win, Atom prop, Atom type, long *value);
long      getdefaultatomval(const char *name, long *value);
void      setatomval(Display *display, Window win, Atom prop, Atom type,
                     unsigned char *data);
void      setdefaultatomval(const char *name, unsigned char *data);
Display * getdisplay(void);
Window    getrootwindow(Display *display);
Atom      getatom(Display *display, const char *name);
int       closedisplay(Display *display);

#ifdef __cplusplus
}
#endif

#endif /* ATLAS_ATOM_H */
