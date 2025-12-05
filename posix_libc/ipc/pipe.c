#include <stdio.h>
#include <unistd.h>

int main() {
  int fds[2];
  char *buff[20];

  if (-1 == pipe(fds)) {
    perror("pipe");
  }
  int ret = fork();

  if (-1 == ret) {
    perror("fork");
  }
  if (0 != ret) {
    close(STDOUT_FILENO);
    dup(fds[1]);
    close(fds[0]);
    execlp("ls", "ls", NULL);
  } else {
    close(STDIN_FILENO);
    dup(fds[0]);
    close(fds[1]);
    execlp("wc", "wc", "-l", NULL);
  }

  return 0;
}