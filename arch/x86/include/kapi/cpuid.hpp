#ifndef _KAPI_X86_CPUID_H
#define _KAPI_X86_CPUID_H

#include <stdint.h>

const uint32_t kExtendedCpuidNR = 0x80000000;

class CpuidRegs {
   private:
    uint32_t eax_, ebx_, ecx_, edx_;

   public:
    CpuidRegs() : eax_(0), ebx_(0), ecx_(0), edx_(0) {}
    CpuidRegs(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx)
        : eax_(eax), ebx_(ebx), ecx_(ecx), edx_(edx) {}

    // getters and setters
    uint32_t eax() const { return eax_; }
    uint32_t ebx() const { return ebx_; }
    uint32_t ecx() const { return ecx_; }
    uint32_t edx() const { return edx_; }
    void set_regs(uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t edx) {
        eax_ = eax, ebx_ = ebx, ecx_ = ecx, edx_ = edx;
    }
};

static inline void cpuid(CpuidRegs* regs) {
    uint32_t eax, ebx, ecx, edx;

    asm volatile("cpuid"
                 : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                 : "a"(regs->eax()), "c"(regs->ecx())
                 : "memory");

    regs->set_regs(eax, ebx, ecx, edx);
}

#endif  // _KAPI_X86_CPUID_H
