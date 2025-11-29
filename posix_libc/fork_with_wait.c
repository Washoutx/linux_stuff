#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void SIGCHLD_Handler() { puts("SIGCHLD handled"); }

int main() {

  signal(SIGCHLD, SIGCHLD_Handler);

  int status;
  pid_t pid = fork();
  if (-1 == pid) {
    perror("fork");
  } else if (0 == pid) {
    kill(getpid(), SIGKILL);
    // abort();
    // exit(EXIT_SUCCESS);
  } else {
    printf("pid=%d\n", pid);
    // pid = wait(&status);
    pid = waitpid(pid, &status, 0);
    printf("pid=%d\n", pid);
    if (-1 == pid) {
      perror("waitpid");
    }
    if (WIFEXITED(status)) {
      printf("Child process finished with status=%d\n", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status)) {
      printf("Child terminated by signal=%d (%s)\n", WTERMSIG(status),
             WCOREDUMP(status) ? "CORE DUMP" : "");
    }
    return 0;
  }
}