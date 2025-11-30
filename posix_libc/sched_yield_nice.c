#include <complex.h>
#include <sched.h>
#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {

  // doesnt work on Docker because container doesn't have CAP_SYS_NICE
  // can be fixed by docker run --cap-add=SYS_NICE ... (I didnt check that);
  int err_or_nice = nice(-20);
  if (err_or_nice == -1) {
    perror("nice");
  }
  printf("Current nice value=%d\n", nice(0));

  printf("Current process priority value=%d\n",
         getpriority(PRIO_PROCESS, getpid()));

  int ret = sched_yield();
  if (-1 == ret) {
    perror("sched_yield");
  }

  return 0;
}