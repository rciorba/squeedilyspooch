#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cerrno>

extern "C"{
#include<sys/socket.h>
#include <netinet/in.h>	/* needed for sockaddr_in */
}


#include"network.h"
using namespace std;
char buffer[512] = {};

void die(int status_code, char* msg=NULL) {
  if(status_code >= 0){ //handle stuff that returns -1 instead of a valid FD
    return;
  }
  cout << "He's dead, Jim!" << endl;
  cout << "returned:" << status_code << endl;
  cout << errno <<endl;
  if (msg != NULL) {
    cout << msg << endl;
  }
  exit(1);
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
  cout<<"recv"<<endl;
  cout << sizeof buffer<< "  "<< (void*)buffer << endl;
  die(rcv->count = recvfrom(sock, (void*)buffer, 512 , 0, (sockaddr*)&from_addr, &addr_len));
  cout<<"count:"<<rcv->count<<endl;
  return rcv;

}
