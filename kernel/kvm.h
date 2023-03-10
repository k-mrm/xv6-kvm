struct xv6_kvm_vcpu {
  struct proc *proc;
  struct xv6_kvm *vm;

  struct spinlock lock;

  int used;
};

struct xv6_kvm {
  struct xv6_kvm_vcpu *vcpus[8];

  struct spinlock lock;

  int used;
};

extern struct xv6_kvm xv6_kvm;
