#include <fried/stdio.h>

int puts_(const char* string) {
	return printf("%s\n", string);
}