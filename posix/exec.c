#include <stdio.h>
#include <unistd.h>

int main() {
  int ret = execl("/bin/vim", "vim", "data.txt", NULL);
  if (ret != 0) {
    perror("execl");
  }
  return 0;
}