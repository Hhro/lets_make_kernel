#include <fried/stdio.h>
#include <keyboard.hpp>

char kGetch() {
    char c;
    c = terminal_getchar();

    return c;
}