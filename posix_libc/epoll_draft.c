#include <fcntl.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <unistd.h>

int main() {
  int fd = open("data.txt", O_CREAT | O_RDWR);
  if (-1 == fd) {
    perror("open");
  }
  int epfd;
  epfd = epoll_create1(0);
  if (-1 == epfd) {
    perror("epoll_create1 failed");
  }

  struct epoll_event ev;
  ev.events = EPOLLIN | EPOLLOUT;
  ev.data.fd = fd;

  int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
  if (ret) {
    perror("epoll_ctl");
  }

  while (1) {
    int nr_events = epoll_wait(epfd, &ev, 1, 100);
    if (nr_events < 0) {
      perror("epoll_wait");
    }
    if (nr_events == 0) {
      puts("timeout");
      break;
    }
  }

  close(fd);
  close(epfd);
  return 0;
}