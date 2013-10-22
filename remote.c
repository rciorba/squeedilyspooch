#include<stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/extensions/XTest.h>

int main(int argc, char**argv) {
  Display* display;
  display = XOpenDisplay(NULL);
  /* XTestFakeMotionEvent(display, screen_number, x, y, delay); */
  XTestFakeMotionEvent(display, 1, 10, 10, 1);
  printf("Hello World\n");
}
