#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "proc.h"

struct kvm_device {
  struct spinlock lock;
} kvmdev;

static int
kvmdevioctl(void *dev, int request, void *buf) {
  (void)dev;
  struct kvm_device *kvmd = &kvmdev;

  printf("KERNEL: kvmdevioctl %p\n", kvmd);

  return 0;
}

static int
kvmdevread(int a, uint64 b, int c) {
  (void)a;
  (void)b;
  (void)c;

  return -1;
}

static int
kvmdevwrite(int a, uint64 b, int c) {
  (void)a;
  (void)b;
  (void)c;

  return -1;
}

void
kvmdevinit(void) {
  devsw[XV6KVM].read = kvmdevread;
  devsw[XV6KVM].write = kvmdevwrite;
  devsw[XV6KVM].ioctl = kvmdevioctl;
}
