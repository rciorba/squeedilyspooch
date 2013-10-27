struct s_recieved {
  int count;
  const char* data;
};
typedef struct s_recieved Recieved;

int open_listening_socket(void);
Recieved* get_data(int);
