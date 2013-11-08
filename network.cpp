#include<iostream>
#include<cstring>

extern "C"{
#include<sys/socket.h>
#include <netinet/in.h>	/* needed for sockaddr_in */
}

#include"network.h"
#include"util.h"

using namespace std;
char buffer[512] = {};


Message::Message(const char* data){
  cmd = htons(*(uint16_t*) data);
  arg = htonl(*(uint32_t*) (data+2));
}

Message** Message::from_recieved(Recieved* rcv){
  die(rcv->count % Message::size,
      (char*)"recieved buffer should have been a multiple of 6");
  int count = rcv->count / Message::size;
  Message** messages = new Message*[count+1];
  cout<<sizeof messages<<endl;
  //static_cast<Message*> (::operator new (sizeof(Message[count])));
  for(int i=0; i<count; i++) {
    messages[i] = new Message(rcv->data);
  }
  messages[count] = NULL;
  return messages;
}


int open_listening_socket(void) {
  int sock_fd;
  struct sockaddr_in server_addr;
  die(sock_fd = socket(AF_INET, SOCK_DGRAM, 0));
  memset((void*)&server_addr, 0, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(6666);
  die(bind(sock_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)));
  return sock_fd;
}


Recieved* get_data(int sock) {
  Recieved* rcv;
  sockaddr_storage from_addr;
  socklen_t addr_len;
  memset((void*)&from_addr, 0, sizeof from_addr);
  rcv = new Recieved();
  rcv->data = buffer;
  // cout<<"recv"<<endl;
  // cout << sizeof buffer<< "  "<< (void*)buffer << endl;
  die(rcv->count = recvfrom(sock, (void*)buffer, 512 , 0, (sockaddr*)&from_addr, &addr_len));
  // cout<<"count:"<<rcv->count<<endl;
  return rcv;
}
