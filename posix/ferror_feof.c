#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  FILE *file = fopen("data.txt", "w+");
  if (NULL == file) {
    perror("fopen failed");
    return -1;
  }

  char buffer[] = "data...";
  int ret = fputs(buffer, file);
  if (ret == -1) {
    perror("fputs failed");
    return -1;
  }
  ret = fseek(file, 0, SEEK_SET);
  if (ret == -1) {
    perror("fputs failed");
    return -1;
  }
  char buffer_read[LINE_MAX];
  if (0 == fread(buffer_read, strlen(buffer) + 1, 1, file)) {
    if (feof(file)) {
      puts("fread returns eof");
    }
    if (ferror(file)) {
      perror("fread failed");
    }
  }

  clearerr(file);

  close(fileno(file));
  if (0 == fread(buffer_read, strlen(buffer), 1, file)) {
    if (feof(file)) {
      puts("fread returns eof");
    }
    if (ferror(file)) {
      perror("fread failed");
    }
  }
  return 0;
}