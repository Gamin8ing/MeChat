#include <sys/socket.h>
#include <stdio.h>
#include "darray.c"

// this is the server, the clients i.e. the peers needs to connect
// to the server to only get the info about another peers, serves as a middle
// ground between peers, like a peer will connect to the server to get the info
// about another peer and then connect to that peer, and then they talk to each
// other
int main() {
  // printf("Hello world!\n");
  int sockfd;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Socket Creation");
    return 1;
  }
  printf("> Socket created successfully\n");
  // pr();
  return 0;
}
