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

struct xv6_kvm kvms[8];
struct xv6_kvm_vcpu kvm_vcpus[16];

static struct xv6_kvm_vcpu *
alloc_kvm_vcpu() {
  struct xv6_kvm_vcpu *v;

  for(v = kvm_vcpus; v < &kvm_vcpus[16]; v++) {
    acquire(&v->lock);

    if(v->used == 0)
      goto found;
    else
      release(&v->lock);
  }

  return 0;

found:
  v->used = 1;
  release(&v->lock);

  return v;
}

static struct xv6_kvm *
alloc_kvm() {
  struct xv6_kvm *kvm;

  for(kvm = kvms; kvm < &kvms[8]; kvm++) {
    acquire(&kvm->lock);

    if(kvm->used == 0)
      goto found;
    else
      release(&kvm->lock);
  }

  return 0;

found:
  kvm->used = 1;
  release(&kvm->lock);

  return kvm;
}

void
xv6_kvm_init(void) {
  struct xv6_kvm *kvm;
  struct xv6_kvm_vcpu *v;

  for(kvm = kvms; kvm < &kvms[8]; kvm++) {
    initlock(&kvm->lock, "kvm");
    kvm->used = 0;
  }
  for(v = kvm_vcpus; v < &kvm_vcpus[16]; v++) {
    initlock(&v->lock, "kvm_vcpu");
    v->used = 0;
  }
}
