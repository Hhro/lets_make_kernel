#ifndef _STRING_H
#define _STRING_H 1

#include <stddef.h>
#include <stdint.h>

int memcmp(const void *aptr, const void *bptr, unsigned long long size);
void *memcpy(void *dstptr, const void *srcptr, unsigned long long size);
void *memset(void *bufptr, unsigned char value, unsigned long long size);
size_t strlen(const char*);

#endif
