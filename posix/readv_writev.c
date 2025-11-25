#include <bits/types/struct_iovec.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/uio.h>

int main() {
  int fd = open("data.txt", O_RDWR | O_CREAT);

  char buff[] = "data...";
  struct iovec write_buffers[2] = {{.iov_base = buff, .iov_len = strlen(buff)},
                                   {.iov_base = buff, .iov_len = strlen(buff)}};

  // NULL means that buffers will be created automatically
  struct iovec read_buffers[2] = {{.iov_base = NULL, .iov_len = 3},
                                  {.iov_base = NULL, .iov_len = 200}};

  ssize_t ret = writev(fd, write_buffers, 2);
  printf("Wrote=%zd", ret);
  return 0;
}