#ifndef _KAPI_X86_MSR_INDEX_H
#define _KAPI_X86_MSR_INDEX_H

<<<<<<< HEAD
#define MSR_APIC_BASE_BSP_BIT 8
#define MSR_APIC_BASE_ENABLE_BIT 11
#define MSR_APIC_BASE_BASE_BIT 12
#define MSR_APIC_BASE_BASE_LEN 5
=======
// MSR APIC(0x8)
#define MSR_APIC_BASE_BSP_BIT       0x08
#define MSR_APIC_BASE_ENABLE_BIT    11
#define MSR_APIC_BASE_BASE_BIT      12
#define MSR_APIC_BASE_BASE_LEN      5
>>>>>>> [ADD] msr-index related to TSC

#define MSR_APIC_BASE_BSP _BIT(MSR_APIC_BASE_BSP_BIT)
#define MSR_APIC_BASE_ENABLE _BIT(MSR_APIC_BASE_ENABLE_BIT)
#define MSR_APIC_BASE_BASE \
    (_MASK(MSR_APIC_BASE_BASE_LEN) << MSR_APIC_BASE_BASE_BIT)

<<<<<<< HEAD
#define MSR_EFER 0xC0000080
#define MSR_EFER_LME_BIT 8
#define MSR_EFER_LME _BIT(MSR_EFER_LME_BIT)
=======
// MSR TSC(0x10)
#define MSR_TIME_STAMP_COUNTER      0x10

// MSR TSC_ADJUST(0x3B)
#define MSR_TSC_ADJUST              0x3B

// MSR TSC_DEADLINE
#define MSR_TSC_DEADLINE            0x06E0

// MSR EFER(0xC0000080)
#define MSR_EFER            0xC0000080
#define MSR_EFER_LME_BIT    8
#define MSR_EFER_LME        _BIT(MSR_EFER_LME_BIT)
>>>>>>> [ADD] msr-index related to TSC

// MSR TSC_AUX(0xC0000103)
#define MSR_TSC_AUX         0xC0000103

#ifndef __ASSEMBLER__
const int kMsrApicBase = 0x1B;
#endif  //__ASSEMBLER__

#endif  //_KAPI_X86_MSR_H