#include "idt.h"
#include<stdint.h>

void outb(uint8_t v, uint16_t port){
    __asm__ __volatile__("outb %0,%1" : : "a" (v), "dN" (port));
}

extern "C" void terminal_putchar(char);

extern "C" void irq0_handler(void) {
    terminal_putchar('!');
    outb(0x20, 0x20); //EOI
}
 
extern "C" void irq1_handler(void) {
	  outb(0x20, 0x20); //EOI
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