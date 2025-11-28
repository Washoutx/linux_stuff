#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// pwrite / popen doesn't manipulate the position in file.
// I don't need to write lseek(...)

int main() {
  // int fd = creat("data.txt", 0777); - creat is only for writing, like open
  // with O_WRONLY | O_CREAT | O_TRUNC

  int fd = open("data.txt", O_RDWR | O_CREAT);

  if (-1 == fd) {
    perror("creat() failed");
  }

  const char write_buffer[] = "Data...";
  size_t size = strlen(write_buffer);
  if (-1 == pwrite(fd, write_buffer, size, (off_t)0)) {
    perror("pwrite failed");
  }

  if (-1 == ftruncate(fd, (off_t)2)) {
    perror("ftruncate failed");
  }

  char read_buffer[256];
  if (-1 == pread(fd, read_buffer, size, (off_t)0)) {
    perror("pread failed");
  }

  printf("File data=%s", read_buffer);

  if (-1 == close(fd)) {
    perror("close failed");
  }

  // Cleanup, file will be removed from memory when all fd is closed, and all
  // processes doesn't operate on it
  if (-1 == unlink("data.txt")) {
    perror("unlink failed");
  }

  return 0;
}