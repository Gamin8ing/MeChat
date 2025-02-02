#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include "darray.c"
#include <error.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define PORT 8080

darr clients;

void *handle_new_clients(void *csockfd) {
  int client_sockfd = *(int *)csockfd;

  pb(clients, client_sockfd); // pushing back the client socket file descriptor
  // exitting out of the thread
  pthread_exit(NULL);
  return 0;
}

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
  GREEN; // color macros defined in utils.c
  printf("> Socket created successfully!\n");
  clients =
      initDArray(); // initialised the dynamic array for clients connecting

  // --------- binding the socket to the localhost at port PORT -----
  struct sockaddr_in server_addr;
  socklen_t server_addr_len;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(PORT);
  server_addr.sin_family = AF_INET;
  server_addr_len = sizeof(server_addr);

  if (bind(sockfd, (struct sockaddr *)&server_addr, server_addr_len) == -1) {
    perror("Binding");
    return 1;
  }
  printf("> Socket bound successfully!\n");

  // --------- putting the socket in a listening state -------------
  if (listen(sockfd, MAX_CLIENTS) == -1) {
    perror("Listening");
    return 1;
  }
  printf("> Socket listening for connections!\n");

  // --------- accepting incoming connection request ---------------
  while (1) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len;
    RCOLOR;
    printf("Looking for clients..");
    int csockfd = (accept(sockfd, (struct sockaddr *)&client_addr,
                          &client_addr_len) == -1);

    // handling max client connections logic,
    // TODO implement/create the protocol for error msging
    if (clients->size == MAX_CLIENTS - 1) {
      // send an error of server full
      const char *errmsg =
          "\033[0;31mSORRY server is currently full!\033[0m \n";
      send(csockfd, errmsg, strlen(errmsg), 0);
      continue;
    }
    if (csockfd == -1) {
      perror("Accepting");
      return 1;
    }

    GREEN;
    printf("Connection accepted: peer #%d \n", clients->size + 1);

    // my plan for the newly joined clients is share the peers connected list
    // with them first i.e. sharing the address of the connected peers for them
    // to communicate with themselves for multiple clients i will be threading
    // the process and the server will remain connected? or should it not? we'll
    // see about this
    pthread_t id;
    int th = pthread_create(&id, NULL, handle_new_clients, (void *)&csockfd);
    if (th != 0) {
      perror("Thread Creation");
      return 1;
    }
    pthread_detach(id);
  }

  close(sockfd);
  free(clients);
  RCOLOR;
  return 0;
}
