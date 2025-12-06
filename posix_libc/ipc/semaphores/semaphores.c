#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

int main() {
  struct sembuf sembuf;
  key_t key = ftok("semaphore_file", 2137);
  if (key == -1) {
    perror("ftok");
  }

  int sem_gid = semget(key, 2, 0666 | IPC_CREAT);
  if (-1 == sem_gid) {
    perror("semget");
  }

  struct sembuf p = {.sem_num = 0, .sem_op = 1, .sem_flg = 0};
  struct sembuf v = {.sem_num = 0, .sem_op = -1, .sem_flg = 0};

  semop(sem_gid, &p, 1);
  semop(sem_gid, &p, 1);

  int curr_val = semctl(sem_gid, 0, GETVAL);
  printf("Semaphor value=%d\n", curr_val);

  semop(sem_gid, &v, 1);
  semop(sem_gid, &v, 1);

  curr_val = semctl(sem_gid, 0, GETVAL);
  printf("Semaphor value=%d\n", curr_val);

  semctl(sem_gid, 0, IPC_RMID);

  return 0;
}