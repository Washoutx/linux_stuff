#include <stdio.h>
#include <stdlib.h>

void post_mortem1() { puts("Programing execution ended1."); }
void post_mortem2() { puts("Programing execution ended2."); }

int main() {

  atexit(post_mortem1);
  atexit(post_mortem2);

  return 0;
  size_t t;
  ssize_t t;
}