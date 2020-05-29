#ifndef ARCH_X86_INCLUDE_UAPI_STRING_HPP_
#define ARCH_X86_INCLUDE_UAPI_STRING_HPP_

#include <stdint.h>

int memcmp(const void *aptr, const void *bptr, uint64_t size);
void *memcpy(void *dstptr, const void *srcptr, uint64_t size);
void *memset(void *bufptr, unsigned char value, uint64_t size);

#endif  // ARCH_X86_INCLUDE_UAPI_STRING_HPP_
