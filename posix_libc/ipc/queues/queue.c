#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

struct my_msg {
  long mtype;
  struct msg_data {
    int a, b;
  } data;
};

int main() {

  key_t key = ftok("queue_config", 2137);
  if (key == -1) {
    perror("ftok");
  }

  int msgid = msgget(key, 0666 | IPC_CREAT);
  if (-1 == msgid) {
    perror("msgget");
  }

  struct my_msg msg1 = {.mtype = 1, .data = {.a = 10, .b = 20}};
  struct my_msg msg2 = {.mtype = 2, .data = {.a = 30, .b = 40}};

  int ret = msgsnd(msgid, &msg1, sizeof(msg1.data), 0);
  if (-1 == ret) {
    perror("msgsnd");
  }
  ret = msgsnd(msgid, &msg2, sizeof(msg2.data), 0);
  if (-1 == ret) {
    perror("msgsnd");
  }

  struct my_msg rec_msg;
  ret = msgrcv(msgid, &rec_msg, sizeof(rec_msg.data), 2, 0);
  printf("a=%d, b=%d\n", rec_msg.data.a, rec_msg.data.b);
  ret = msgctl(msgid, IPC_RMID, NULL);
  if (-1 == ret) {
    perror("msgctl");
  }
  return 0;
}