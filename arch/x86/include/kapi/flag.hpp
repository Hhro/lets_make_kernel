#ifndef ARCH_X86_INCLUDE_KAPI_FLAG_HPP_
#define ARCH_X86_INCLUDE_KAPI_FLAG_HPP_

#define EFLAGS_ID (1 << 21)

#ifndef __ASSEMBLER__

#include <kapi/const.hpp>
bool IsFlagChangable(const u32 flag);

#endif  // __ASSEMBLER

#endif  // ARCH_X86_INCLUDE_KAPI_FLAG_HPP_
