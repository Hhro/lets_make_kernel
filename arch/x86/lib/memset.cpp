#include <kapi/string.hpp>

void* memset(void* bufptr, unsigned char value, uint64_t size) {
    unsigned char* buf = reinterpret_cast<unsigned char*>(bufptr);
    for (uint64_t i = 0; i < size; i++) buf[i] = value;
    return bufptr;
}
