#include <stdint.h>

#include <kapi/string.hpp>

int memcmp(const void* aptr, const void* bptr, uint64_t size) {
    const unsigned char* a = reinterpret_cast<const unsigned char*>(aptr);
    const unsigned char* b = reinterpret_cast<const unsigned char*>(bptr);
    for (uint64_t i = 0; i < size; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}