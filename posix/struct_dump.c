#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define VALIDATE_RETURN(ret, msg)                                              \
  do {                                                                         \
    if (ret < 0) {                                                             \
      perror(msg);                                                             \
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

  ret =
      fflush(NULL); // NULL means all process stream data are push out to kernel
  VALIDATE_RETURN(ret, "fflush failed");
  fsync(fileno(file)); // Sync to physical mem but not needed here.

  errno = 0;    // reset errno since rewind is void
  rewind(file); // pos=begin in file
  if (errno != 0) {
    perror("rewind failed");
  }

  ret = fread(&d_dest, sizeof(Data), 1, file);
  VALIDATE_RETURN(ret, "fread failed");

  printf(".buffer=%s, .state=%d, .is_valid=%d", d_dest.buffer, d_dest.state,
         d_dest.is_valid);

  ret = fclose(file);
  VALIDATE_RETURN(ret, "fclose failed");

  ret = unlink("data.txt");
  VALIDATE_RETURN(ret, "unlink failed");
  return 0;
}