#include<iostream>

extern "C"{
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#include <X11/extensions/XTest.h>
}

#include "network.h"

using namespace std;


class MDisplay {
  Display* disp;
  // uint32_t SIGN_X = 1;
 public:
  MDisplay();
  void mouse_move(uint32_t arg);
  void mouse_press(void);
  void mouse_release(void);
};

MDisplay::MDisplay(){
  disp = XOpenDisplay(":0");
}

void MDisplay::mouse_move(uint32_t arg) {
}

void MDisplay::mouse_press() {
}

void MDisplay::mouse_release() {
}
void dispatch_message(MDisplay display, Message* msg){
  // switch(msg->cmd){
  // case Messages::M_MOVE:
  // }
  // this won't work; needs constexpr
  if (msg->cmd == Messages::M_MOVE){
    display.mouse_move(msg->arg);
  } else if(msg->cmd == Messages::M_PRESS1) {
    display.mouse_press();
  } else if(msg->cmd == Messages::M_RELEASE1) {
    display.mouse_release();
  }
}


void dispatch_messages(MDisplay display, int sock){
  Recieved* rcv = get_data(sock);
  Message** messages = Message::from_recieved(rcv);
  int i = 0;
  while(messages[i]) {
    dispatch_message(display, messages[i]);
    i++;
  }
}

int main(int argc, char** argv) {
  // Display* display = XOpenDisplay(":0");
  // int ev_br, er_br, maj_v, min_v;
  // int socket;
  // if (XTestQueryExtension(display, &ev_br, &er_br, &maj_v, &min_v)) {
  //   cout << "XTestQuery is supported" << endl;
  // }
  // /* XTestFakeMotionEvent(display, screen_number, x, y, delay); */
  // // XTestFakeMotionEvent(display, -1, 1, 1, CurrentTime); 
  // // XWarpPointer(display, None, 0, 0, 0, 0, 0, 100, 100);
  // XTestFakeButtonEvent(display, 1, True, CurrentTime);

  // XFlush(display);
  // XTestFakeButtonEvent(display, 1, False, CurrentTime);

  // XFlush(display);
  // socket = open_listening_socket();
  // Recieved* rcv;
  // cout << "-" << endl;
  // rcv = get_data(socket);
  // cout << "-" << endl;
  // cout.write(rcv->data, max(rcv->count, 512));
  // cout.flush();
  Messages::initialize();
  cout << "Hello World" << endl;
  // unsigned int i = 0;
  char txt[] = {0,1,0,0,0,0, 0,1,0,0,0,0};
  cout<<"sizeof input data "<<sizeof txt<<endl;
  // cout<<txt<<endl;
  // i=*(uint16_t*)txt;

  // cout<<i<<endl;
  Recieved rcvd = Recieved();
  rcvd.data = txt;
  rcvd.count = sizeof txt;
  Message** messages = Message::from_recieved(&rcvd);
  int i=0;
  cout<<(1<<1)<<endl;
  while(messages[i]){
    cout<<"spam!"<<endl;
    i++;
  }
  delete messages;
  cout<<"bye"<<endl;
}
