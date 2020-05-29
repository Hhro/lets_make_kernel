#ifndef ARCH_X86_INCLUDE_KAPI_TSC_HPP_
#define ARCH_X86_INCLUDE_KAPI_TSC_HPP_

#include <kapi/asm-generic.hpp>
#include <kapi/cpuinfo.hpp>

static inline bool IsTscAvail() { return cpu_info.CpuHas(X86_FEATURE_TSC); }
static inline bool IsTscAdjustAvail() {
    return cpu_info.CpuHas(X86_FEATURE_TSC_ADJUST);
}
static inline bool IsTscDeadline() {
    return cpu_info.CpuHas(X86_FEATURE_TSCDEADLINE);
}

static inline unsigned long long rdtsc() {
    DECLARE_ARGS(low, high);

    asm volatile(
        "rdtsc\n"
        "\n"
        : EAX_EDX_RET(low, high)
        :
        : "memory");

    return EAX_EDX_VAL(low, high);
}

#endif  // ARCH_X86_INCLUDE_KAPI_TSC_HPP_