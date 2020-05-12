#include <kapi/const.hpp>
#include <kapi/string.hpp>

int memcmp(const void* aptr, const void* bptr, u64 size) {
    const unsigned char* a = reinterpret_cast<const unsigned char*>(aptr);
    const unsigned char* b = reinterpret_cast<const unsigned char*>(bptr);
    for (u64 i = 0; i < size; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}