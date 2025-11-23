#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
  fd_set readfds;
  struct timeval timeout;

  FD_ZERO(&readfds); // cleanup
  FD_SET(STDIN_FILENO, &readfds);

  timeout.tv_sec = 5;
  timeout.tv_usec = 0;

  puts("Wait for intput data for 5 seconds...");
  int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
  if (-1 == ret) {
    perror("select failed");
  } else if (0 == ret) {
    perror("timeout");
  } else {
    if (FD_ISSET(STDIN_FILENO, &readfds)) {
      const size_t size = 256;
      char buffer[size + 1];

      int len = read(STDIN_FILENO, buffer, size);
      if (-1 == len) {
        perror("read failed");
      }
      if (len) {
        buffer[len] = '\0';
        printf("Read=%s", buffer);
      }
    }
  }
  // FILE* -> _IO_FILE* struct is a wrapper for file descriptos created by LibC
  // when file is opened.
  return 0;
}