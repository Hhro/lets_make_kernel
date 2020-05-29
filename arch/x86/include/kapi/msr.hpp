#ifndef _KAPI_X86_MSR_H
#define _KAPI_X86_MSR_H

#include <kapi/asm-generic.hpp>
#include <kapi/msr-index.hpp>

#ifndef __ASSEMBLER__
#include <stdint.h>
static inline unsigned long long rdmsr(unsigned int msr_id) {
    DECLARE_ARGS(eax, edx);

    asm volatile(
        "1: rdmsr \n"
        "2:\n"
        : EAX_EDX_RET(eax, edx)
        : "c"(msr_id));

    return EAX_EDX_VAL(eax, edx);
}

static inline void wrmsr(unsigned int msr_id, uint32_t low, uint32_t high) {
    asm volatile(
        "1: wrmsr \n"
        "2:\n"
        :
        : "c"(msr_id), "a"(low), "d"(high)
        : "memory");
}

#endif  // __ASSEMBLER__

#endif  //_KAPI_X86_MSR_H
