#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <arch/common.hpp>
#include <error.hpp>
#include <vga.h>
 
extern "C" void kernel_main(void);

void kernel_main(void) 
{
	arch_init();
	terminal_initialize();
	
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello Kernel");
	while(1) {}

	// unreachable code
	unreachable_error();
}
