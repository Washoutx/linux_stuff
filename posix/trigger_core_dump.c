#include <string.h>
int main() {
  int *ptr = NULL;
  int val = *ptr;

  return 0;
}
// gcc -g trigger_core_dump.c
// invoke program...
// zsh: segmentation fault (core dumped)  ./a.out

// based on the following output few things can happen, following pattern just
// create core file
// cat /proc/sys/kernel/core_pattern
// > core

// it can be use with gdb
//  gdb a.out core

/*
Program terminated with signal SIGSEGV, Segmentation fault.
#0  0x0000aaaae47a0724 in main () at trigger_core_dump.c:4
4         int val = *ptr;
(gdb) print ptr
$1 = (int *) 0x0
*/