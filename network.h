#ifndef SQUIGGLY_NET_H
#define SQUIGGLY_NET_H

extern "C"{
#include<sys/socket.h>
#include <netinet/in.h>	/* needed for sockaddr_in */
}

struct s_recieved {
  int count;
  const char* data;
};
typedef struct s_recieved Recieved;


class Messages {
public:
  static uint16_t M_MOVE, M_PRESS1, M_RELEASE1;
  static void initialize();
};


class Message{
  uint16_t cmd;
  uint32_t arg;
public:
  Message(char*);
  char* encode(void);
};


int open_listening_socket(void);
Recieved* get_data(int);
#endif
