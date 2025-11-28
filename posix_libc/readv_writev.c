#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/uio.h>
#include <unistd.h>

int main() {
  int fd = open("data.txt", O_RDWR | O_CREAT);

  char write_buffer1[] = "data1...";
  char write_buffer2[] = "data2...";
  struct iovec write_buffers[2] = {
      {.iov_base = write_buffer1, .iov_len = strlen(write_buffer1)},
      {.iov_base = write_buffer2, .iov_len = strlen(write_buffer2)}};

  char read_buffer1[3] = {0};
  char read_buffer2[200] = {0};
  struct iovec read_buffers[2] = {
      {.iov_base = read_buffer1, .iov_len = sizeof(read_buffer1)},
      {.iov_base = read_buffer2, .iov_len = sizeof(read_buffer2)}};

  ssize_t ret =
      writev(fd, write_buffers, sizeof(write_buffers) / sizeof(struct iovec));
  printf("Wrote status=%zd\n", ret);

  lseek(fd, 0, SEEK_SET);

  ret = readv(fd, read_buffers, sizeof(read_buffers) / sizeof(struct iovec));
  printf("Read status=%zd\n", ret);
  printf("Read buffer[0]=%s | buffer[1]=%s", (char *)read_buffers[0].iov_base,
         (char *)read_buffers[1].iov_base);
  return 0;
}