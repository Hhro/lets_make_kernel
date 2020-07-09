#include <fried/stdio.h>
#include <keyboard.hpp>
#include <vga.h>

void _putchar(char character) {
    char c = (char) character;
    if (c == KEY_BACKSPACE)
        terminal_backspace(true);
    else
        terminal_write(&c, sizeof(c));

    return;
}