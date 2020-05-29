#include <fried/stdio.h>

char kGetch() {
    char c;
    c = terminal_getchar();

    return c;
}