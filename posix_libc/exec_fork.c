#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid == -1) {
    perror("fork");
  } else if (pid > 0) {
    puts("parent");
  } else {
    puts("child");
    int ret = execl("/bin/ls", "ls", NULL);
    if (ret != 0) {
      perror("execl");
    }
    exit(EXIT_SUCCESS);
  }

  return 0;
}