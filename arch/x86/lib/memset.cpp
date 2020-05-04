#include <kapi/string.hpp>

void* memset(void* bufptr, unsigned char value, u64 size) {
    unsigned char* buf = reinterpret_cast<unsigned char*>(bufptr);
    for (u64 i = 0; i < size; i++)
        buf[i] = value;
    return bufptr;
}
