#define _GNU_SOURCE

#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/user.h>
#include <unistd.h>

int main() {
  int fd = open("data.bin", O_RDWR | O_CREAT, 0666);
  if (-1 == fd) {
    perror("open");
    return -1;
  }
  //   int page_size = sysconf(_SC_PAGESIZE);
  int page_size = getpagesize();
  if (-1 == ftruncate(fd, page_size)) {
    perror("ftruncate");
  }

  char *ptr = mmap(NULL, page_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap");
    close(fd);
    return -1;
  }
  ptr[0] = 255;

  char *ptr2 = mremap(ptr, page_size, page_size * 2, 0);
  if (ptr2 == MAP_FAILED) {
    perror("mremap failed");
    return 1;
  }

  if (-1 == mprotect(ptr2, page_size * 2, PROT_READ | PROT_EXEC)) {
    perror("mprotec");
  }

  if (-1 == msync(ptr2, page_size * 2, MS_SYNC)) {
    perror("msyc");
  }

  if (-1 == munmap(ptr, page_size)) {
    perror("munmap");
    return -1;
  }
  close(fd);

  return 0;
}