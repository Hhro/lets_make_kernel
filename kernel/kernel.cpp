#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <common.hpp>
#include <error.hpp>
#include <vga.h>
#include <kapi/cpuinfo.hpp>
#include <stdio.hpp>
 
extern "C" void kernel_main(void);

void kernel_main(void) 
{
	arch_init();
	terminal_initialize();
	DKeyboard.Activate();
	
	/* Newline support is left as an exercise. */
	while(1){
		uint8_t ch;
		ch = getChar();
		terminal_putchar(ch);
	}
	
	__asm__ __volatile__(
		"end_loop: hlt\t\n"
		"jmp end_loop"
		::
	);
}
