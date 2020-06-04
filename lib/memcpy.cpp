#include <fried/string.h>

void __attribute__((weak)) *memcpy(void *dstptr, const void *srcptr, unsigned long long size) {
	unsigned char* dst = (unsigned char*) dstptr;
	const unsigned char* src = (unsigned char*) srcptr;
	for (size_t i = 0; i < size; i++)
		dst[i] = src[i];
	return dstptr;
}