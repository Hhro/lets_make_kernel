#ifndef _X86_IDT_H
#define _X86_IDT_H
#include<stdint.h>

struct IDTDescr {
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t type_attr; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
};

void outb(uint8_t v, uint16_t port);
extern "C" void irq0_handler(void);
extern "C" void irq1_handler(void);
extern "C" void irq2_handler(void);
extern "C" void irq3_handler(void);
extern "C" void irq4_handler(void);
extern "C" void irq5_handler(void);
extern "C" void irq6_handler(void);
extern "C" void irq7_handler(void);
extern "C" void irq8_handler(void);
extern "C" void irq9_handler(void);
extern "C" void irq10_handler(void);
extern "C" void irq11_handler(void);
extern "C" void irq12_handler(void);
extern "C" void irq13_handler(void);
extern "C" void irq14_handler(void);
extern "C" void irq15_handler(void);
void set_IDT_entry(struct IDTDescr * entry, uint64_t offset, uint16_t selector, uint8_t ist, uint8_t type);

#endif