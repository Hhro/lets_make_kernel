#include <kapi/idt.hpp>
#include <keyboard.h>
#include<stdint.h>

void set_IDT_entry(struct IDTDescr * entry, uint64_t offset, uint16_t selector, uint8_t ist, uint8_t type){
    entry->ist = ((ist & 0x7)&0xff);
    entry->offset_1 = (offset)&0xffff;
    entry->offset_2 = (offset>>16)&0xffff;
    entry->offset_3 = (offset>>32)&0xffffffff;
    entry->selector = selector;
    entry->type_attr = type;
    entry->zero = 0;

    return;
}

extern "C" void bp_handler(void){
    terminal_putchar('#');
}

extern "C" void double_fault_handler(void){
    terminal_putchar('@');
    __asm__ __volatile__(
		"end_loop: hlt\t\n"
		"jmp end_loop"
		::
	);
}

extern "C" void irq0_handler(void) {
    outb(0x20, 0x20); //EOI
}
 
extern "C" void irq1_handler(void) { //key board
    uint8_t scancode, cv, mode;
    __asm__ __volatile(
        "cli"::
    );

    scancode = inb(0x60);
    cv = inb(0x61);

    outb(0x61, cv | 0x80);
    outb(0x61, cv);

    switch(scancode){
        case CAPSLOCK:
            is_Caps = is_Caps^1;
            goto end_handler;
        case LSHIFT:
        case RSHIFT:
            on_Shift = 1;
            goto end_handler;
        case LSHIFT | 0x80:
        case RSHIFT | 0x80:
            on_Shift = 0;
            goto end_handler;
    }
    if(scancode <= 0x7f){
        mode = (on_Shift) ? 1 : (is_Caps ? (asccode[scancode][0]>='a' && asccode[scancode][0]>='z' ? 1 : 0): 0);
        terminal_putchar(asccode[scancode][mode]);
    }

    end_handler:
	outb(0x20, 0x20); //EOI
    __asm__ __volatile(
        "sti"::
    );
}
 
extern "C" void irq2_handler(void) {
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq3_handler(void) {
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq4_handler(void) {
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq5_handler(void) {
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq6_handler(void) {
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq7_handler(void) {
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq8_handler(void) {
          outb(0xA0, 0x20);
          outb(0x20, 0x20); //EOI          
}
 
extern "C" void irq9_handler(void) {
          outb(0xA0, 0x20);
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq10_handler(void) {
          outb(0xA0, 0x20);
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq11_handler(void) {
          outb(0xA0, 0x20);
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq12_handler(void) {
          outb(0xA0, 0x20);
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq13_handler(void) {
          outb(0xA0, 0x20);
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq14_handler(void) {
          outb(0xA0, 0x20);
          outb(0x20, 0x20); //EOI
}
 
extern "C" void irq15_handler(void) {
          outb(0xA0, 0x20);
          outb(0x20, 0x20); //EOI
}