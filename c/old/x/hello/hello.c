#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int errno;

int
main(void)
{
	Display *d;
	Window w;
	XEvent e;

	const char *msg = "Hello, World!";
	int s;

	/* Connect to the X server. */
	if (!(d = XOpenDisplay(getenv("DISPLAY")))) {
		printf("XOpenDisplay: Can't connect X server: %s\n", strerror(errno));
		exit(1);
	}

	s = XDefaultScreen(d);

	/* Create window. */
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 200, 200, 1,
	                        XBlackPixel(d, s), XWhitePixel(d, s));

	/* Events we get to handle. */
	XSelectInput(d, w, ExposureMask | KeyPressMask);

	/* Show window on the screen. */
	XMapWindow(d, w);

	/* Infinite event handling loop. */
	for (;;) {
		XNextEvent(d, &e);

		/* Redraw window on exposing. */
		if (e.type == Expose) {
			XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
			XDrawString(d, w, DefaultGC(d, s), 50, 50, msg, strlen(msg));
		}

		/* Exit when pressed button get. */
		if (e.type == KeyPress)
			break;
	}

	/* Close connection to the display. */
	XCloseDisplay(d);

	return 0;
}
