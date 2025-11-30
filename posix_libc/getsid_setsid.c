#include <stdio.h>
#include <unistd.h>

int main() {
  printf("parent sid=%d\n", getsid(getpid()));
  printf("parent pgid=%d\n", getpgid(getpid()));

  pid_t pid = fork();

  if (0 == pid) {
    printf("child sid=%d\n", getsid(getpid()));
    printf("child pgid=%d\n", getpgid(getpid()));
    pid_t sid = setsid();
    int ret = setpgid(getpid(), 1234);
    if (ret == -1) {
      perror("setpgid");
    }
    printf("child sid=%d\n", getsid(getpid()));
    printf("child pgid=%d\n", getpgid(getpid()));
  }
  return 0;
}