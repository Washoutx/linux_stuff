#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t my_pid = getpid();
  pid_t parent_pid = getppid();

  printf("my pid=%d, parent pid=%d\n", my_pid, parent_pid);
  // fflush(stdout);
  //   while (1) {
  //   };
  return 0;
}