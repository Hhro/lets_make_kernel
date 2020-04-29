#ifndef ARCH_X86_INCLUDE_KAPI_FLAG_HPP_
#define ARCH_X86_INCLUDE_KAPI_FLAG_HPP_

#include <kapi/const.hpp>

const u32 EFLAGS_ID = (1 << 21);

bool IsFlagChangable(const u32 flag);

#endif  // ARCH_X86_INCLUDE_KAPI_FLAG_HPP_
