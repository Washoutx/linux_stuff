#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define port 8080

int main() {
  struct sockaddr_in sock_addr = {.sin_family = AF_INET,
                                  .sin_port = htons(port)};
  // internet presentation to network, converts address server from string
  // to binary bin
  if (inet_pton(AF_INET, "127.0.0.1", &sock_addr.sin_addr) < 0) {
    perror("inet_pton");
  }

  int client_sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == client_sock_fd) {
    perror("socket");
  }

  if (connect(client_sock_fd, (struct sockaddr *)&sock_addr,
              sizeof(sock_addr)) < 0) {
    perror("connect");
  }

  char msg[] = "Hello from client\n";
  send(client_sock_fd, msg, strlen(msg), 0);
  printf("Hello message sent to server\n");

  char buffer[200];
  read(client_sock_fd, buffer, sizeof(buffer));
  printf("Server: %s\n", buffer);

  return 0;
}
