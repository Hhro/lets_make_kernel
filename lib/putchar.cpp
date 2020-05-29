#include <fried/stdio.h>
#include <vga.h>

int kPutchar(int ic) {
    char c = (char) ic;
	terminal_write(&c, sizeof(c));

    return ic;
}