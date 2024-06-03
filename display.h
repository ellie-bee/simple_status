#pragma once
#include <X11/Xlib.h>

Display *get_display();
void free_display(Display *display);

void display_status(Display *display, const char *status);
