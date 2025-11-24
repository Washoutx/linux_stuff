#include <bits/posix2_lim.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  FILE *file = fopen("data1.txt", "w+");
  if (NULL == file) {
    perror("fopen failed");
  }
  char buffer[] = "hello world...\n data...";
  fprintf(file, "%s", buffer);
  // fflush push data from Cbuffer to kernel
  // it is not mean data will be pushed to harddrive (sync/fsync)
  fflush(file);
  fseek(file, 0, SEEK_SET);

  // fgetc / ungetc just modify pointer in Cbuffer, nothing changed with
  // original data.
  int ch = fgetc(file);
  if (EOF == ch) {
    puts("fgets failed");
  }
  printf("char=%c\n", (char)ch);

  ch = ungetc(ch, file);
  if (EOF == ch) {
    puts("ungetc failed");
  }
  printf("char=%c\n", (char)ch);

  ch = fgetc(file);
  if (EOF == ch) {
    puts("fgets failed");
  }
  printf("char=%c\n", (char)ch);
  ch = fgetc(file);
  if (EOF == ch) {
    puts("fgets failed");
  }
  printf("char=%c\n", (char)ch);

  char buffer_read_line[LINE_MAX];
  char *buffer_ptr = fgets(buffer_read_line, LINE_MAX, file);
  if (NULL == buffer_ptr) {
    perror("fgets failed");
  }
  printf("line=%s", buffer_ptr);
  return 0;
}