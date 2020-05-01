#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "keyboard.h"
#include "terminal.h"
#include "../arch/x86/descriptors/gdt.h"
 
extern "C" void kernel_main(void);

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!\n");
	initialize_gdt_tss();
	terminal_writestring("[+] GDT and TSS initialization success\n");
	initialize_idt_tables();
	terminal_writestring("[+] IDT Table initialization success\n");

	if (activate_keyboard()) {
		terminal_writestring("[+] Keyboard activation success\n");
	}
	else {
		terminal_writestring("[!] Keyboard activation failed\n");
	}
	
}