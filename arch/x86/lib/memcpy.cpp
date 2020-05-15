#include <kapi/string.hpp>

void* memcpy(void* dstptr, const void* srcptr, u64 size) {
    unsigned char* dst = reinterpret_cast<unsigned char*>(dstptr);
    const unsigned char* src = reinterpret_cast<const unsigned char*>(srcptr);

    for (u64 i = 0; i < size; i++)
        dst[i] = src[i];

    return dst;
}