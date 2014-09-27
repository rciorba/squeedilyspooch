#include<iostream>
#include<cerrno>
#include<cstdlib>

using namespace std;

void die_nonzero(int value, const char* msg=NULL) {
  if(value == 0){
    return;
  }
  cout << "He's dead, Jim!" << endl;
  cout << "Call returned:" << value << endl;
  cout << "Errno is:" << errno <<endl;
  if (msg != NULL) {
    cout << msg << endl;
  }
  exit(1);
}

void die(int value, const char* msg=NULL) {
  if(value >= 0){
    return;
  }
  cout << "He's dead, Jim!" << endl;
  cout << "Call returned:" << value << endl;
  cout << "Errno is:" << errno <<endl;
  if (msg != NULL) {
    cout << msg << endl;
  }
  exit(1);
}
