#ifndef _X86_IDT_H
#define _X86_IDT_H
#include <stdint.h>

#ifndef __ASEMBLER__
#pragma pack( push, 1 )
struct IDTDescr {
   uint16_t offset_1; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t type_attr; // type and attributes
   uint16_t offset_2; // offset bits 16..31
   uint32_t offset_3; // offset bits 32..63
   uint32_t zero;     // reserved
};

struct TSSSEGMENT {
   uint32_t reserved1;
   uint64_t rsp[3];
   uint64_t reserved2;
   uint64_t ist[7];
   uint64_t reserved3;
   uint16_t reserved4;
   uint16_t io_base;
};
#pragma pack(pop)

static inline void outb(uint16_t port, uint8_t v){
    __asm__ __volatile__("outb %0,%1" : : "a" (v), "dN" (port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

void set_IDT_entry(struct IDTDescr * entry, uint64_t offset, uint16_t selector, uint8_t ist, uint8_t type);
void idt_init(void);

extern "C" int break_point();
extern "C" int double_fault();
extern "C" int irq0();
extern "C" int irq1();
extern "C" int irq2();
extern "C" int irq3();
extern "C" int irq4();
extern "C" int irq5();
extern "C" int irq6();
extern "C" int irq7();
extern "C" int irq8();
extern "C" int irq9();
extern "C" int irq10();
extern "C" int irq11();
extern "C" int irq12();
extern "C" int irq13();
extern "C" int irq14();
extern "C" int irq15();

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
extern "C" void break_point_handler(void);
extern "C" void double_fault_handler(void);

extern "C" void terminal_putchar(char);
#endif
#endif