#include <fried/stdio.h>
#include <vga.h>

void _putchar(char character) {
    char c = (char) character;
    terminal_write(&c, sizeof(c));

    return;
}