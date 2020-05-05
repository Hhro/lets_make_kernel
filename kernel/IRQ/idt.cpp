#include "idt.h"
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

void set_GDT_entry8(struct GDTDescr_8 * entry, uint32_t baseaddress, uint32_t limit, uint8_t upperflag, uint8_t lowerflag, uint8_t type){
    entry->lowerlimit = limit & 0xffff;
    entry->upperlimit_upperflag = upperflag | (limit >> 16)&0x0f;
    entry->type_lowerflag = lowerflag | type;
    entry->base_address1 = baseaddress & 0xffff;
    entry->base_address2 = (baseaddress >> 16) & 0xff;
    entry->base_address3 = (baseaddress >> 24) & 0xff;

    return;
}

void set_GDT_entry16(struct GDTDescr_16 * entry, uint64_t baseaddress, uint32_t limit, uint8_t upperflag, uint8_t lowerflag, uint8_t type){
    entry->lowerlimit = limit & 0xffff;
    entry->upperlimit_upperflag = (limit >> 16)&0xff | upperflag;
    entry->type_lowerflag = lowerflag | type;
    entry->base_address1 = baseaddress & 0xffff;
    entry->base_address2 = (baseaddress >> 16) & 0xff;
    entry->base_address3 = (baseaddress >> 24) & 0xff;
    entry->base_address4 = baseaddress >> 32;
    entry->reserved = 0;
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
    terminal_putchar('!');
    outb(0x20, 0x20); //EOI
}
 
extern "C" void irq1_handler(void) { //key board
    uint8_t scancode;
    scancode = inb(0x60);


    
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