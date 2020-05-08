#ifndef _X86_IDT_H
#define _X86_IDT_H
#include <stdint.h>

#define GDT_TYPE_CODE 0xa
#define GDT_TYPE_DATA 0x2
#define GDT_TYPE_TSS 0x9
#define GDT_FLAG_LOWER_S 0x10
#define GDT_FLAG_LOWER_DPL0 0x00
#define GDT_FLAG_LOWER_DPL1 0x20
#define GDT_FLAG_LOWER_DPL2 0x40
#define GDT_FLAG_LOWER_DPL3 0x60
#define GDT_FLAG_LOWER_P 0x80
#define GDT_FLAG_UPPER_L 0x20
#define GDT_FLAG_UPPER_G 0x80

#define GDT_FLAG_LOWER_KCODE (GDT_FLAG_LOWER_S|GDT_FLAG_LOWER_DPL0|GDT_FLAG_LOWER_P)
#define GDT_FLAG_UPPER_KCODE (GDT_FLAG_UPPER_G|GDT_FLAG_UPPER_L)
#define GDT_FLAG_LOWER_KDATA (GDT_FLAG_LOWER_S|GDT_FLAG_LOWER_DPL0|GDT_FLAG_LOWER_P)
#define GDT_FLAG_UPPER_KDATA (GDT_FLAG_UPPER_G|GDT_FLAG_UPPER_L)
#define GDT_FLAG_LOWER_TSS (GDT_FLAG_LOWER_DPL0|GDT_FLAG_LOWER_P)
#define GDT_FLAG_UPPER_TSS GDT_FLAG_UPPER_G


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

struct GDTDescr_8 {
   uint16_t lowerlimit;
   uint16_t base_address1;
   uint8_t base_address2;
   uint8_t type_lowerflag;
   uint8_t upperlimit_upperflag;
   uint8_t base_address3;
};

struct GDTDescr_16{
   uint16_t lowerlimit;
   uint16_t base_address1;
   uint8_t base_address2;
   uint8_t type_lowerflag;
   uint8_t upperlimit_upperflag;
   uint8_t base_address3;
   uint32_t base_address4;
   uint32_t reserved;
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
void set_GDT_entry8(struct GDTDescr_8 * entry, uint32_t baseaddress, uint32_t limit, uint8_t upperflag, uint8_t lowerflag, uint8_t type);
void set_GDT_entry16(struct GDTDescr_16 * entry, uint64_t baseaddress, uint32_t limit, uint8_t upperflag, uint8_t lowerflag, uint8_t type);

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