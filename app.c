#include <stdio.h>
#include <sys/socket.h>

int main() {
  printf("Hello, World!\n");
  // creating the two sockets for listening sockets (receiving msgs) and passive
  // sockets (sending msgs)
  int listSockfd, passSockfd;
  listSockfd = socket(AF_INET, SOCK_STREAM,
                      0); // SOCK_STREAM for TCP and AF_INET for IPv4 socket
  passSockfd = socket(AF_INET, SOCK_STREAM, 0);

  // checking if the sockets are created successfully
  if (listSockfd < 0 || passSockfd < 0) {
    perror("Socket Creation"); // perror prints the error message based on the
                               // errno value
    return 1;
  }
  printf("> Sockets created successfully\n");
  return 0;
}
