
#include <stdio.h>
#include <sys/poll.h>
#include <unistd.h>

#define TIMEOUT 5000
int main() {
  struct pollfd fds[2] = {{.fd = STDIN_FILENO, .events = POLLIN},
                          {.fd = STDOUT_FILENO, .events = POLLOUT}};

  int ret = poll(fds, 2, TIMEOUT);
  if (ret == -1) {
    perror("poll failed");
    return 1;
  } else if (ret == 0) {
    perror("Timeout");
    return 0;
  }

  puts("Try read");
  if (fds[0].revents & POLLIN) {
    puts("Ready to read from STDIN");
  }
  if (fds[1].revents & POLLOUT) {
    puts("Ready to write to STDOUT");
  }
  return 0;
}
// > ./a.out
// Try read
// Ready to write to STDOUT

// > ./a.out <<< "test"
// Try read
// Ready to read from STDIN
// Ready to write to STDOUT