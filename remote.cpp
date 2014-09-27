#include<iostream>
#include<cstring>

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
  void mouse_move(int x, int y);
  void mouse_press(int btn);
  void mouse_release(int btn);
};

MDisplay::MDisplay(){
  // int ev_br, er_br, maj_v, min_v;
  // die(!XTestQueryExtension(disp, &ev_br, &er_br, &maj_v, &min_v))
  disp = XOpenDisplay(":0");
}

void MDisplay::mouse_move(int x, int y) {
  XWarpPointer(disp, None, 0, 0, 0, 0, 0, x, y);
}

void MDisplay::mouse_press(int btn) {
  XTestFakeButtonEvent(disp, btn, True, CurrentTime);
}

void MDisplay::mouse_release(int btn) {
  XTestFakeButtonEvent(disp, btn, False, CurrentTime);
}

void dispatch_message(MDisplay display, Message* msg){
  // switch(msg->cmd){
  // case Messages::M_MOVE:
  // }
  // this won't work; needs constexpr
  if (msg->cmd == Messages::M_MOVE){
    display.mouse_move(msg->arg1, msg->arg2);
  } else if(msg->cmd == Messages::M_PRESS1) {
    display.mouse_press(msg->arg1);
  } else if(msg->cmd == Messages::M_RELEASE1) {
    display.mouse_release(msg->arg1);
  } else {
    cout << "unmatched message:" << msg->cmd <<"; htons:" << htons(msg->cmd)<<endl;
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


int test(){
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
  // uint16_t uns = 3;
  // uns <<= 15;
  // cout << uns << endl;
  // cout << (int16_t)uns << endl;
  // unsigned int i = 0;
  char txt[] = {0,1, 255,255, 0,0,
                0,0, 0,255, 128,0};
  cout<<"sizeof input data "<<sizeof txt<<endl;
  // cout<<txt<<endl;
  // i=*(uint16_t*)txt;

  // cout<<i<<endl;
  Recieved rcvd = Recieved();
  rcvd.data = txt;
  rcvd.count = sizeof txt;
  Message** messages = Message::from_recieved(&rcvd);
  int i=0;
  while(messages[i]){
    cout << "msg:" << messages[i]->arg1 << ";" << messages[i]->arg2 << ";" << endl;
    i++;
  }
  delete messages;
  cout<<"bye"<<endl;
  return 0;
}

int main(int argc, char** argv) {
  if ((argc>1) && (strcmp(argv[1], "tests") == 0)) {
    return test();
  }
  Messages::initialize();
  MDisplay display = MDisplay();
  int socket;
  socket = open_listening_socket();
  Recieved* rcv;
  while((rcv = get_data(socket))){
    Message** messages = Message::from_recieved(rcv);
    for(int i; messages[i]; i++){
      dispatch_message(display, messages[i]);
    }
  }
}
