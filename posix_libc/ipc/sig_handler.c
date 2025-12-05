#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t flag = 0;

void my_sig_handler(int sig) {
  const char *msg = "SIGINT received, ignore.\n";
  write(STDOUT_FILENO, msg, strlen(msg));
  flag = 2117;
}

int main() {
  struct sigaction my_sigaction = {
      .sa_handler = my_sig_handler, .sa_flags = SA_RESTART, .sa_mask = 0};

  if (-1 == sigaction(SIGINT, &my_sigaction, NULL)) {
    perror("sigaction");
  }

  char IO_buffer[200];
  puts("Provide input:");
  if (fgets(IO_buffer, sizeof(IO_buffer), stdin) == NULL) {
    perror("fgets");
  } else {
    printf("Flag value=%d, Input=%s\n", flag, IO_buffer);
  }
  return 0;
}