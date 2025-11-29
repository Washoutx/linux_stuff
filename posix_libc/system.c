#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int my_system(char *command) {
  pid_t pid = fork();
  if (-1 == pid) {
    printf("[%s] fork failed=%s", __FUNCTION__, strerror(errno));
  }
  if (0 == pid) {
    char *argv[4];
    argv[0] = "sh";
    argv[1] = "-c";
    argv[2] = command;
    argv[3] = NULL;
    execv("/bin/sh", argv);
    exit(EXIT_FAILURE);
  }
  int status;
  int ret = waitpid(pid, &status, 0);
  if (-1 == ret) {
    printf("[%s] waitpid failed=%s", __FUNCTION__, strerror(errno));
  } else if (WIFEXITED(status)) {
    return WEXITSTATUS(status);
  }
  return -1;
}

int main() {
  int ret = system("echo test");
  if (-1 == ret) {
    perror("system");
  } else {
    printf("Return status=%d", WEXITSTATUS(ret));
  }

  return 0;
}