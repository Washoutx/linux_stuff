#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define port 8080

int main() {

  struct sockaddr_in sockaddr = {
      .sin_family = AF_INET,
      .sin_port = htons(port),
      .sin_addr = INADDR_ANY,
  };
  int addrlen = sizeof(sockaddr);

  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == socket_fd) {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  if (bind(socket_fd, (struct sockaddr *)&sockaddr, addrlen) < 0) {
    perror("bind");
  }
  printf("Server listening on port %d\n", port);
  if (listen(socket_fd, 3) < 0) {
    perror("listen");
  }

  int client_sock_fd =
      accept(socket_fd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);

  char buffer[200];
  read(client_sock_fd, buffer, sizeof(buffer));
  printf("Client: %s\n", buffer);
  char msg[] = "Hello from server\n";
  send(client_sock_fd, msg, strlen(msg), 0);

  close(socket_fd);
  close(client_sock_fd);
  return 0;
}
