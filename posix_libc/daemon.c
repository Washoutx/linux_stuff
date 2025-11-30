#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
  int ret = daemon(1, 0);
  if (-1 == ret) {
    perror("daemon");
    exit(EXIT_FAILURE);
  }

  FILE *journal = fopen("daemon_c.logs", "w+");
  if (journal == NULL) {
    perror("fopen");
  }
  while (1) {
    time_t now = time(NULL);
    fprintf(journal, "%s, Logs ...\n", ctime(&now));
    fflush(journal);
    sleep(5);
  }
  fclose(journal);
}