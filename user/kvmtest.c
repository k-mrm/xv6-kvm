#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[]) {
  int fd;

  if((fd = open("kvm", 0)) < 0) {
    fprintf(2, "kvm not found\n");
    exit(1);
  }

  if(ioctl(fd, 0, 0) < 0)
    fprintf(2, "ioctl failed\n");

  close(fd);
  exit(0);
}
