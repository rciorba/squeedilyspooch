#include<iostream>
#include<cerrno>
#include<cstdlib>

using namespace std;

void die(int status_code, const char* msg=NULL) {
  if(status_code == 0){
    return;
  }
  cout << "He's dead, Jim!" << endl;
  cout << "Call returned:" << status_code << endl;
  cout << "Errno is:" << errno <<endl;
  if (msg != NULL) {
    cout << msg << endl;
  }
  exit(1);
}

void die_fd(int fd, const char* msg=NULL) {
  if(fd >= 0){
    return;
  }
  cout << "He's dead, Jim!" << endl;
  cout << "Invalid file descriptor returned:" << fd << endl;
  cout << "Errno is:" << errno <<endl;
  if (msg != NULL) {
    cout << msg << endl;
  }
  exit(1);
}
