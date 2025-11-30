#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  if (_POSIX_SAVED_IDS)
    puts("SAVED IDS supported in the system");

  printf("uid=%d, gid=%d\n", getuid(), getgid());
  printf("euid=%d, egid=%d\n", geteuid(), getegid());
  if (-1 == setgid(1)) {
    perror("setgid");
  }
  if (-1 == setuid(10)) {
    perror("setuid");
  }
  puts("=================================");
  printf("uid=%d, gid=%d\n", getuid(), getgid());
  printf("euid=%d, egid=%d\n", geteuid(), getegid());

  if (-1 == setegid(2)) {
    perror("setegid");
  }
  if (-1 == seteuid(20)) {
    perror("seteuid");
  }
  puts("=================================");
  printf("uid=%d, gid=%d\n", getuid(), getgid());
  printf("euid=%d, egid=%d\n", geteuid(), getegid());
  return 0;
}