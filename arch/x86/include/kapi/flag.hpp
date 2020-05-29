#ifndef ARCH_X86_INCLUDE_KAPI_FLAG_HPP_
#define ARCH_X86_INCLUDE_KAPI_FLAG_HPP_

#define EFLAGS_ID (1 << 21)

#ifndef __ASSEMBLER__

#include <stdint.h>
bool IsFlagChangable(const uint64_t flag);

#endif  // __ASSEMBLER

#endif  // ARCH_X86_INCLUDE_KAPI_FLAG_HPP_
