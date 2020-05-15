#ifndef ARCH_X86_INCLUDE_UAPI_STRING_HPP_
#define ARCH_X86_INCLUDE_UAPI_STRING_HPP_

#include <kapi/const.hpp>

int memcmp(const void *aptr, const void *bptr, u64 size);
void *memcpy(void *dstptr, const void *srcptr, u64 size);
void *memset(void *bufptr, unsigned char value, u64 size);

#endif  // ARCH_X86_INCLUDE_UAPI_STRING_HPP_
