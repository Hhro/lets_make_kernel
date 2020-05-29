#ifndef _KAPI_X86_CR_H
#define _KAPI_X86_CR_H

#include <kapi/const.hpp>

#ifdef __ASSEMBLER__
#define CR0_PE_BIT 0
#define CR0_PE _BIT(CR0_PE_BIT)
#define CR0_PG_BIT 31
#define CR0_PG _BIT(CR0_PG_BIT)

#define CR4_PAE_BIT 5
#define CR4_PAE _BIT(CR4_PAE_BIT)
#else
#include <stdint.h>

const uint32_t CR0_PE_BIT = 0;
const uint32_t CR0_PE = _BIT(CR0_PE_BIT);
const uint32_t CR0_PG_BIT = 31;
const uint32_t CR0_PG = _BIT(CR0_PG_BIT);

const uint32_t CR4_PAE_BIT = 5;
const uint32_t CR4_PAE = _BIT(CR4_PAE_BIT);
#endif  // __ASSEMBLER__

#endif  // _KAPI_X86_CR_H
