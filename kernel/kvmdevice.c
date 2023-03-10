#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "fs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "file.h"
#include "proc.h"
#include "kvm.h"
#include "kvmctl.h"

void xv6_kvm_init(void);

struct kvm_device {
  struct spinlock lock;
  struct xv6_kvm *vm;
} kvmdev;

struct kvm_vm_device {

};

struct kvm_vcpu_device {

};

static int
kvmvmdev_ioctl(void *dev, int req, void *buf) {
  return -1;
}

static int
kvmvcpudev_ioctl(void *dev, int req, void *buf) {
  return -1;
}

static int
kvmdevioctl(void *dev, int req, void *buf) {
  (void)dev;
  struct kvm_device *kvmd = &kvmdev;

  switch(req) {
    case KVM_CREATE_VM:
      printf("kvm create vm\n");
      break;
    default:
      printf("unk\n");
      return -1;
  }

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
  xv6_kvm_init();

  devsw[XV6KVM].read = kvmdevread;
  devsw[XV6KVM].write = kvmdevwrite;
  devsw[XV6KVM].ioctl = kvmdevioctl;

  devsw[XV6KVM_VM].read = 0;
  devsw[XV6KVM_VM].write = 0;
  devsw[XV6KVM_VM].ioctl = kvmvmdev_ioctl;

  devsw[XV6KVM_VCPU].read = 0;
  devsw[XV6KVM_VCPU].write = 0;
  devsw[XV6KVM_VCPU].ioctl = kvmvcpudev_ioctl;
}
