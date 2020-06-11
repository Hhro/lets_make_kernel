#include <fried/string.h>

void __attribute__((weak)) *memset(void *bufptr, unsigned char value, unsigned long long size) {
	unsigned char* buf = (unsigned char*) bufptr;
	for (size_t i = 0; i < size; i++)
		buf[i] = value;
	return bufptr;
}