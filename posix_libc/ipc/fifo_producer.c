#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  if (-1 == mkfifo("fifo_file", 0644)) {
    perror("mkfifo");
  }

  int fd = open("fifo_file", O_WRONLY);
  if (-1 == fd) {
    perror("open");
  }

  char buffer[] = "Hello from other process";

  if (-1 == write(fd, buffer, sizeof(buffer))) {
    perror("write");
  }

  close(fd);
  return 0;
}