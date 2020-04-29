#ifndef _KAPI_X86_CPUFEATURES_H
#define _KAPI_X86_CPUFEATURES_H

#include <kapi/const.hpp>

#define X86_NFEATURES   19

/* Intel CPU features eax = 0x00000001, EDX, word 0*/
#define X86_FEATURE_APIC    (0*32 + 9)

/* Intel CPU features eax = 0x80000001, ECX, word 1*/
#define X86_FEATURE_LAHF_LM     (1*32 + 0)
#define X86_FEATURE_LZCNT       (1*32 + 5)
#define X86_FEATURE_PREFETCHW   (1*32 + 8)

/* Intel CPU features eax = 0x80000001, EDX, word 2*/
#define X86_FEATURE_SYSCALL_SYSRET          (2*32 + 11)
#define X86_FEATURE_EXECUTE_DISABLE_BIT     (2*32 + 20)
#define X86_FEATURE_1GIB_PAGE               (2*32 + 26)
#define X86_FEATURE_RDTSCP_IA32_TSC_AUX     (2*32 + 27)
#define X86_FEATURE_LM_AVAIL                (2*32 + 29)

#endif  //_KAPI_X86_CPUFEATURES_H