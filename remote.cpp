#include<iostream>

extern "C"{
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/extensions/XTest.h>
}
using namespace std;

int main(int argc, char** argv) {
  Display* display = XOpenDisplay(":0");
  int ev_br, er_br, maj_v, min_v;
  if (XTestQueryExtension(display, &ev_br, &er_br, &maj_v, &min_v)) {
    cout << "XTestQuery is supported" << endl;
  }
  /* XTestFakeMotionEvent(display, screen_number, x, y, delay); */
  // XTestFakeMotionEvent(display, -1, 1, 1, CurrentTime);
  // XWarpPointer(display, None, 0, 0, 0, 0, 0, 100, 100);
  XTestFakeButtonEvent(display, 1, True, CurrentTime);

  XFlush(display);
  XTestFakeButtonEvent(display, 1, False, CurrentTime);

  XFlush(display);
  cout << "Hello World" << endl;
}
