#include <bits/types/struct_sched_param.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

void sched_log(int policy) {
  switch (policy) {
  case SCHED_OTHER:
    printf("SCHED_OTHER: Normal\n");
    break;
  case SCHED_RR:
    printf("SCHED_RR: Round robin\n");
    break;
  case SCHED_FIFO:
    printf("SCHED_FIFO: FIFO \n");
    break;
  case -1:
    perror("sched_getscheduler");
    break;
  default:
    fprintf(stderr, "Unknown!\n");
  }
}
int main() {
  int policy;
  policy = sched_getscheduler(getpid());
  sched_log(policy);

  struct sched_param sp = {.sched_priority = 1};

  // doesnt work in docker container due to lack of CAP_SYS_NICE
  policy = sched_setscheduler(getpid(), SCHED_FIFO, &sp);

  policy = sched_getscheduler(getpid());
  sched_log(policy);
  return 0;
}