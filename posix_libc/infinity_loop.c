// for some tests

int main() {
  while (1) {
  };
  return 0;
}

// backgroun process test
// ~/linux_stuff/posix_libc main ?2 > ./a.out &
// 2926
// ~/linux_stuff/posix_libc main ?2 > jobs
// running    ./a.out
// ~/linux_stuff/posix_libc main ?2 > kill 2926
// + terminated  ./a.out
// ~/linux_stuff/posix_libc main ?2 > jobs