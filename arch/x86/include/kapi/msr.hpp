#ifndef _KAPI_X86_MSR_H
#define _KAPI_X86_MSR_H

#include <kapi/const.hpp>

#define MSR_APIC_BASE           0x1B
#define MSR_APIC_BASE_BSP_BIT       8
#define MSR_APIC_BASE_ENABLE_BIT    11
#define MSR_APIC_BASE_BASE_BIT      12
#define MSR_APIC_BASE_BASE_LEN      5

#define MSR_APIC_BASE_BSP       _BIT(MSR_APIC_BASE_BSP_BIT)
#define MSR_APIC_BASE_ENABLE    _BIT(MSR_APIC_BASE_ENABLE_BIT)
#define MSR_APIC_BASE_BASE      (_MASK(MSR_APIC_BASE_BASE_LEN)<<MSR_APIC_BASE_BASE_BIT)

#define MSR_EFER            0xC0000080
#define MSR_EFER_LME_BIT    8
#define MSR_EFER_LME        _BITUL(MSR_EFER_LME_BIT)
#endif
