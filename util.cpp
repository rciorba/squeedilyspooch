#include<iostream>
#include<cerrno>
#include<cstdlib>

using namespace std;

void die(int status_code, char* msg=NULL) {
  if(status_code == 0){
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
