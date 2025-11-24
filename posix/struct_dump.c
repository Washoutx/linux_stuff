#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define VALIDATE_RETURN(ret, msg)                                              \
  do {                                                                         \
    if (ret < 0) {                                                             \
      perror(msg);                                                             \
      return -1;                                                               \
    }                                                                          \
  } while (0)

typedef struct Data {
  char buffer[100];
  int state;
  bool is_valid;
} Data;

int main() {
  Data d_src = {.buffer = "data...", .state = 1, .is_valid = true}, d_dest;

  int ret = {};
  FILE *file = fopen("data.txt", "w+");
  if (NULL == file) {
    perror("fopen failed");
  }

  ret = fwrite(&d_src, sizeof(Data), 1, file);
  VALIDATE_RETURN(ret, "fwrite failed");

  ret = fread(&d_src, sizeof(Data), 1, file);
  VALIDATE_RETURN(ret, "fread failed");

  printf(".buffer=%s, .state=%d, .is_valid=%d", d_src.buffer, d_src.state,
         d_src.is_valid);

  ret = fclose(file);
  VALIDATE_RETURN(ret, "fclose failed");

  ret = unlink("data.txt");
  VALIDATE_RETURN(ret, "unlink failed");
  return 0;
}