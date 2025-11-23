#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  if (flags & O_NONBLOCK) {
    puts("STDIN non block");
  } else {
    puts("STDIN block");
  }

  fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); // returns previous flags
  flags = fcntl(STDIN_FILENO, F_GETFL, 0);
  if (flags & O_NONBLOCK) {
    puts("STDIN non block");
  } else {
    puts("STDIN block");
  }

  const size_t size = 256;
  char buffer[size + 1];

  while (1) {
    int ret = read(STDIN_FILENO, buffer, size);
    if (ret == -1 && errno == EAGAIN) {
      perror("read failed");
      sleep(1);
    } else if (ret > 0) {
      buffer[ret] = '\0'; // fgets adds it automatically but raw read not
      printf("READ=%s", buffer);
      break;
    } else if (ret == 0) {
      perror("no data"); // I think it is not possible in this example
      break;
    } else {
      perror("Read failed");
      break;
    }
  }
  return 0;
}