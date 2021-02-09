/* Made by "k1574". See the license. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <X11/Xutil.h>

void usage(void);

static char *argv0, *fmt = "%02x%02x%02x" ;
static Display *dpy;
static Window dw, root;
static XColor c;
static unsigned int dui; 
static int di, x, y;

void
usage(void)
{
	fprintf(stderr, "Usage: %s [format]\n", argv0);
	exit(1);
}

void
main(int argc, char *argv[]) {
	argv0 = argv[0] ;
	if (argc == 1) ;
	else if (argc == 2) fmt = argv[1] ;
	else usage();
	if(!(dpy = XOpenDisplay(0))) {
		fprintf(stderr, "%s: cannot open display.\n", argv0);
		exit(1);
	}
	root = DefaultRootWindow(dpy) ;
	XQueryPointer(dpy, root, &dw, &dw, &x, &y, &di, &di, &dui);
	c.pixel = XGetPixel(XGetImage(dpy, root, x, y, 1, 1, AllPlanes, ZPixmap), 0, 0) ;
	XQueryColor(dpy, DefaultColormap(dpy, DefaultScreen(dpy)), &c);
	printf(fmt, c.red>>8, c.green>>8, c.blue>>8);
	XCloseDisplay(dpy);
	exit(0);
}

