#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  if (-1 == mkfifo("fifo_file", 0644)) {
    perror("mkfifo");
  }

  int fd = open("fifo_file", O_RDONLY);
  if (-1 == fd) {
    perror("open");
  }

  char buffer[200];
  int read_size = read(fd, buffer, sizeof(buffer));
  if (-1 == read_size) {
    perror("read");
  }

  buffer[read_size] = '\0';

  printf("%s", buffer);
  close(fd);
  return 0;
}