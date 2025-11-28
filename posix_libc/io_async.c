
#include <aio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct aiocb aiocb_t;

int main() {
  int fd = open("data.txt", O_RDWR | O_CREAT, 0777);
  if (-1 == fd) {
    perror("open");
    return -1;
  }

  char data_to_write[] = "Async writing...";

  aiocb_t io_write;
  memset(&io_write, 0, sizeof(aiocb_t));
  io_write.aio_fildes = fd;
  io_write.aio_buf = data_to_write;
  io_write.aio_nbytes = strlen(data_to_write);
  io_write.aio_offset = 0;

  if (-1 == aio_write(&io_write)) {
    perror("aio_write");
  }
  while (EINPROGRESS == aio_error(&io_write)) {
    puts("Wait for async write..");
  }

  int written = aio_return(&io_write);
  printf("Async written bytes=%d", written);
  close(fd);
  return 0;
}