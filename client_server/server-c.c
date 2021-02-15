/*****************************************************************************
 * server-c.c
 * Name:
 * BU ID:
 * Email:
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

/* TODO: server()
 * Open socket and wait for client to connect
 * Print received message to stdout
 * Return 0 on success, non-zero on failure
*/
int server(char *server_port) {
  // create socket file descriptor
  int server_fd; // server_fd is the file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // create socket address
  // forcefully attach socket to the port
  struct sockaddr_in address;
  int opt = 1;
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
  {
    perror("setsockopt failed");
    exit(EXIT_FAILURE);
  }
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(atoi(server_port));

  // bind socket to address
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // listen to incoming connections
  // this puts the server socket in a passive mode, where it waits for the client to 
  // approach the server to make a connection
 if (listen(server_fd, QUEUE_LENGTH) < 0)
  {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  int sock;
  int addrlen = sizeof(address);
  int recv_bytes;
  char buffer[RECV_BUFFER_SIZE];

  while (1)
  {
    // accept a connection
    // sock is a new connected socket with a new file descriptor 
    // referring to that socket
    if ((sock = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    {
      perror("accept failed");
      exit(EXIT_FAILURE);
    }

    // receive message
    while (1)
    {
      recv_bytes = recv(sock, buffer, RECV_BUFFER_SIZE, 0); 
      if (recv_bytes <= 0) // TODO: packet interrupt error
      {
        // printf("\nI'm breaking!"); 
        break;
      }
      
      fwrite(buffer, sizeof(char), recv_bytes, stdout); 
      fflush(stdout);

    }
    
    // close socket
    close(sock);
  }

  // TODO ctrl+c exit commands or server() function never return

  return 0;
}

/*
 * main():
 * Parse command-line arguments and call server function
*/
int main(int argc, char **argv) {
  char *server_port;

  if (argc != 2) {
    fprintf(stderr, "Usage: ./server-c [server port]\n");
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  return server(server_port);
}
