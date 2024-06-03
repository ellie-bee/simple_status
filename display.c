
#include "display.h"

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

void display_status(Display *display, const char *status) {
  int res = XStoreName(display, DefaultRootWindow(display), status);
  if (!res) {
    fprintf(stderr, "Failed to set status");
    exit(-1);
  }
  XFlush(display);
}

Display *get_display() {
  Display *display = XOpenDisplay(NULL);
  if (!display) {
    fprintf(stderr, "Failed to open display");
    exit(-1);
  }
  return display;
}

void free_display(Display *display) {
  XStoreName(display, DefaultRootWindow(display), NULL);
  if (XCloseDisplay(display) < 0) {
    fprintf(stderr, "Failed to close display");
    exit(-1);
  }
}
