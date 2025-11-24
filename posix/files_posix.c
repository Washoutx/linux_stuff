#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  // Default program descriptos
  printf("in=%d, out=%d, err=%d\n", STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO);

  // fopen() is C-function, open() is a syscall
  FILE *fd1 = fopen("data1.txt", "w+");
  if (NULL == fd1) {
    perror("fopen failed");
  }
  int fd2 = open("data2.txt", O_RDWR | O_CREAT, 0777);

  if (-1 == fd2) {
    perror("open failed");
  }
  printf("Files open success fd1=%d, fd2=%d\n", fileno(fd1), fd2);

  const char buffer_write[] = "data...";
  const size_t LENGTH = strlen(buffer_write);

  if (-1 == fwrite(buffer_write, sizeof(char), LENGTH, fd1)) {
    perror("fwrite failed");
  }

  // Following function push data from C-lib buffers(STDIO) to kernel
  fflush(fd1);
  // Data are stored in internal kernel buffers in RAM (cache pages), following
  // function transfers data to physical storage (updates also metadata from
  // i-node). /proc/sys/vm/dirty_expire_centisecs this is max time for buffer
  // storation Dirty pages are pages with data different than contains physical
  // storage. fsync will be called after every write if file is opened with
  // O_SYNC flag, write function will end after the fsync(), big perfor. impact
  fsync(fd2);

  if (-1 == write(fd2, buffer_write, LENGTH)) {
    perror("write failed");
  }

  fseek(fd1, (off_t)0, SEEK_SET);
  lseek(fd2, (off_t)0, SEEK_SET);

  char buffer_read[256];
  if (-1 == fread(buffer_read, sizeof(char), LENGTH, fd1)) {
    perror("fread failed");
  }
  puts(buffer_read);

  memset(buffer_read, 0, 256);
  if (-1 == read(fd2, buffer_read, LENGTH)) {
    perror("read failed");
  }
  puts(buffer_read);

  if (-1 == fclose(fd1)) {
    perror("fclose failed");
  }
  if (-1 == close(fd2)) {
    perror("close failed");
  }

  puts("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  // errno usage
  errno = EPIPE;
  puts(strerror(errno));

  // Test log to different streams
  fprintf(stderr, "Error log test %s\n", "ERROR");
  fprintf(stdout, "Error log test %s\n", "ERROR");

  // creat (file, 0644); == open (file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

  // Cleanup, file will be removed from memory when all fd is closed, and all
  // processes doesn't operate on it
  if (0 != remove("data1.txt")) // Clib variant, calls unlink under the hood
  {
    perror("remove failed");
  }
  if (-1 == unlink("data1.txt")) {
    perror("unlink failed");
  }
  return 0;
}
