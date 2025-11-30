

#include <stdio.h>
#include <sys/resource.h>

int main() {
  struct rlimit rl;
  int ret = getrlimit(RLIMIT_STACK, &rl);
  if (-1 == ret) {
    perror("getrlimit");
  }
  printf("Stack size limit=%lu mb\n", rl.rlim_cur / 1024 / 1024);
  printf("Stack size max limit=%lu gb\n", rl.rlim_max / 1024 / 1024 / 1024);

  struct rlimit new_rl = {.rlim_cur = 4 * 1024 * 1024,
                          .rlim_max = RLIM_INFINITY};
  ret = setrlimit(RLIMIT_STACK, &new_rl);
  if (-1 == ret) {
    perror("setrlimit");
  }
  ret = getrlimit(RLIMIT_STACK, &rl);
  if (-1 == ret) {
    perror("getrlimit");
  }
  printf("Stack size limit=%lu mb\n", rl.rlim_cur / 1024 / 1024);
  printf("Stack size max limit=%lu gb\n", rl.rlim_max / 1024 / 1024 / 1024);

  return 0;
}