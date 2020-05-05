#ifndef _KAPI_X86_CPUID_H
#define _KAPI_X86_CPUID_H

#include <kapi/const.hpp>

const u32 kExtendedCpuidNR = 0x800000000;

class CpuidRegs {
 private:
  u32 eax_, ebx_, ecx_, edx_;
 public:
  CpuidRegs():
    eax_(0), ebx_(0), ecx_(0), edx_(0) {}
  CpuidRegs(u32 eax, u32 ebx, u32 ecx, u32 edx):
    eax_(eax), ebx_(ebx), ecx_(ecx), edx_(edx) {}

  // getters and setters
  u32 eax() const { return eax_; }
  u32 ebx() const { return ebx_; }
  u32 ecx() const { return ecx_; }
  u32 edx() const { return edx_; }
  void set_regs(u32 eax, u32 ebx, u32 ecx, u32 edx) {
      eax_ = eax, ebx_ = ebx, ecx_ = ecx, edx_ = edx;
  }
};

static inline void cpuid(CpuidRegs* regs) {
    u32 eax, ebx, ecx, edx;

    asm volatile(
        "cpuid"
        : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
        : "m" (regs->eax()), "m" (regs->ecx())
        : "memory"
    );

    regs->set_regs(eax, ebx, ecx, edx);
}

#endif  // _KAPI_X86_CPUID_H
