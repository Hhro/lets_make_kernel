#include <kapi/string.hpp>

void* memcpy(void* dstptr, const void* srcptr, uint64_t size) {
    unsigned char* dst = reinterpret_cast<unsigned char*>(dstptr);
    const unsigned char* src = reinterpret_cast<const unsigned char*>(srcptr);

    for (uint64_t i = 0; i < size; i++) dst[i] = src[i];

    return dst;
}