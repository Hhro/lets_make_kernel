#ifndef _KAPI_X86_MSR_H
#define _KAPI_X86_MSR_H

#include <kapi/const.hpp>
#include <kapi/msr-index.hpp>

#define DECLARE_ARGS(val, low, high)    unsigned long low, high
#define EAX_EDX_VAL(val, low, high) ((low) | (high) << 32)
#define EAX_EDX_RET(val, low, high) "=a" (low), "=d" (high)

static inline unsigned long long rdmsr(unsigned int msr_id){
    DECLARE_ARGS(val, low, high);

    asm volatile(
        "1: rdmsr \n"
        "2:\n"
        : EAX_EDX_RET(val, low, high) : "c" (msr_id)
    );

    return EAX_EDX_VAL(val, low, high);
}

static inline void wrmsr(unsigned int msr_id, u32 low, u32 high){
    asm volatile(
        "1: wrmsr \n"
        "2:\n"
        : : "c" (msr_id), "a" (low), "d" (high) : "memory"
    );
}

#endif  //_KAPI_X86_MSR_H
