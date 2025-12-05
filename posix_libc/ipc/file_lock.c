#include <fcntl.h>

int main() {

  struct flock fl = {
      .l_type = F_WRLCK,
      .l_whence = SEEK_SET,
      .l_start = 0,
      .l_len = 0,
  };

  int fd = open("lock_file", O_WRONLY);
  fcntl(fd, F_SETLKW, &fl);

  return 0;
}