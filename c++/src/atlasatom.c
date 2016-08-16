/* *****************************************************************************
 * 
 * Name:    atlasatom.cc
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

/* Includes */
#include "atlasatom.h"
#include <stdbool.h>
#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/* ************************************************************************** */
/* Return atom value */
long getatomval(Display *display, Window win, Atom prop, Atom type, long *value)
{
	int  di;
	unsigned long  dl;
	unsigned char *p = NULL;
	Atom da;

    if ((XGetWindowProperty(display, win, prop, 0L, sizeof(Atom), false, type,
                            &da, &di, &dl, &dl, &p) == Success) && p)
    {
        *value = *((long*)p) & ((1LL << di) - 1);
        XFree(p);
    }
    return *value;
}

/* ************************************************************************** */
/* Return atom value from default display and window */
long getdefaultatomval(const char *name, long *value)
{
    Display *display = getdisplay();
    Window   root    = getrootwindow(display);
    Atom     prop    = getatom(display, name);
    long     ret     = getatomval(display, root, prop, XA_CARDINAL, value);
    closedisplay(display);
    return ret;
}

/* ************************************************************************** */
/* Set atom value */
void setatomval(Display *display, Window win, Atom prop, Atom type,
                unsigned char *data)
{
    XChangeProperty(display, win, prop, type, 32, PropModeReplace, data, 1);
}

/* ************************************************************************** */
/* Set atom value for default display and window */
void setdefaultatomval(const char *name, unsigned char *data)
{
    Display *display = getdisplay();
    Window   root    = getrootwindow(display);
    Atom     prop    = getatom(display, name);
    setatomval(display, root, prop, XA_CARDINAL, data);
    closedisplay(display);
}

/* ************************************************************************** */
/* Return display */
Display * getdisplay(void)
{
    static Display *display;
    display = XOpenDisplay(NULL);
    return display;
}

/* ************************************************************************** */
/* Return root window */
Window getrootwindow(Display *display)
{
    static Window root;
    int screen = DefaultScreen(display);
	root = RootWindow(display, screen);
    return root;
}

/* ************************************************************************** */
/* Return specified atom */
Atom getatom(Display *display, const char *name)
{
    static Atom atom;
    atom = XInternAtom(display, name, true);
    return atom;
}

/* ************************************************************************** */
/* Close the display and clean up used memory */
int closedisplay(Display *display)
{
    return XCloseDisplay(display);
}
