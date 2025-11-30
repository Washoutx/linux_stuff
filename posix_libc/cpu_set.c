#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  cpu_set_t set;
  CPU_ZERO(&set);
  sched_getaffinity(0, sizeof(set), &set);
  int count = 0;
  for (int i = 0; i < CPU_SETSIZE; i++) {
    if (CPU_ISSET(i, &set))
      count++;
  }

  printf("CPUs for this pid: %d\n", count);

  CPU_ZERO(&set);
  CPU_SET(0, &set);
  int ret = sched_setaffinity(getpid(), sizeof(cpu_set_t), &set);

  CPU_ZERO(&set);
  sched_getaffinity(0, sizeof(set), &set);
  count = 0;
  for (int i = 0; i < CPU_SETSIZE; i++) {
    if (CPU_ISSET(i, &set))
      count++;
  }
  printf("CPUs for this pid: %d\n", count);

  return 0;
}