#include <stdio.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>

int main() {
  key_t key = ftok("shmem_key_generator", 2137);
  if (key == -1) {
    perror("ftok");
  }

  int shm_id = shmget(key, 1024 /*size of shm in bytes*/, 0666 | IPC_CREAT);
  if (-1 == shm_id) {
    perror("shmget");
  }

  char *data = shmat(shm_id, NULL, 0);
  if (data == MAP_FAILED) {
    perror("shmat");
  }
  shmdt(data);
  shmctl(shm_id, IPC_RMID, 0);
  return 0;
}