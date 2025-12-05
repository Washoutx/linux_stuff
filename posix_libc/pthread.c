#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *foo(void *arg) {
  printf("THREAD PID=%d, TID=%d\n", getpid(), gettid());
  return NULL;
}

int main() {
  pthread_t thread;
  int ret = pthread_create(&thread, NULL, foo, NULL);
  if (-1 == ret) {
    perror("pthread_create");
  }
  if (-1 == pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL)) {
    perror("pthread_setcanceltype");
  }
  if (-1 == pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL)) {
    perror("");
  }
  printf("MAIN PID=%d, TID=%d\n", getpid(), gettid());
  if (-1 == pthread_cancel(thread)) {
    perror("pthread_cancel");
  }
  pthread_detach(thread);
  // pthread_join(thread, NULL);

  return 0;
}