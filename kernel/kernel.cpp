#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <arch.hpp>
#include <vga.h>
 
extern "C" void kernel_main(void);

void kernel_main(void) 
{
	arch_init();
	terminal_initialize();
	
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello Kernel");
	
	__asm__ __volatile__(
		"end_loop: hlt\t\n"
		"jmp end_loop"
		::
	);
}
