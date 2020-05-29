#include <fried/stdio.h>

int kPuts(const char* string) {
	return kPrintf("%s\n", string);
}