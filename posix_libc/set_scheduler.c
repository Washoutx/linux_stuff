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

  printf("FIFO prio min = %d\n", sched_get_priority_min(SCHED_FIFO));
  printf("FIFO prio max = %d\n", sched_get_priority_max(SCHED_FIFO));
  printf("Round robin prio min = %d\n", sched_get_priority_min(SCHED_RR));
  printf("Round robin prio max = %d\n", sched_get_priority_max(SCHED_RR));

  struct timespec ts;
  int ret = sched_rr_get_interval(getpid(), &ts);
  if (-1 == ret) {
    perror("sched_rr_get_interval");
  }
  printf("RR time interval=%.2lf miliseconds",
         (ts.tv_sec * 1000.0f) + ts.tv_nsec / 1000000.0f);
  return 0;
}