#include <limits.h>
#include <stdio.h>
#include <unistd.h>

#define VALIDATE_RETURN(ret, msg)                                              \
  do {                                                                         \
    if (ret < 0) {                                                             \
      perror(msg);                                                             \
    }                                                                          \
  } while (0)

int main() {
  int ret = 0;
  FILE *file = fopen("data.txt", "w+");
  if (NULL == file) {
    perror("fopen failed");
    return -1;
  }

  ret = fprintf(file, "test,data,file");
  VALIDATE_RETURN(ret, "fprintf failed");
  ret = fseek(file, 0, SEEK_SET);
  VALIDATE_RETURN(ret, "fseek failed");

  size_t size = LINE_MAX;
  char buffer[size];
  char *s = buffer;
  char delimiter = ',';

  while (--size > 0 && (ret = fgetc(file)) != EOF && (*s++ = ret) != delimiter)
    ;
  ;

  if (ret == delimiter) {
    *(--s) = '\0';
  } else {
    *s = '\0';
  }

  printf("data=%s", buffer);

  ret = fclose(file);
  VALIDATE_RETURN(ret, "fclose failed");

  ret = unlink("data.txt");
  VALIDATE_RETURN(ret, "unlink failed");
  return 0;
}