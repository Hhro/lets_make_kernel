#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kapi/cpuinfo.hpp>
#include <kapi/idt.hpp>
#include <kapi/gdt.hpp>
#include "include/vga.h"
 
extern "C" void kernel_main(void);

struct IDTDescr IDT[256];
uint64_t idt_ptr[2]={0,};

struct GDTDescr_8 GDT[5];
uint64_t gdt_ptrr[2]={0,};

struct TSSSEGMENT TSS;

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


void tss_init(struct TSSSEGMENT * tss){
	extern void * stack2;
	tss->ist[0] = ((uint64_t)&stack2)+0x1000;
	tss->io_base = 0xffff;
	
	return;
}

void gdt_init(void){
	uint64_t gdt_address;

	set_GDT_entry8(&GDT[0], 0, 0, 0, 0);
	set_GDT_entry8(&GDT[1], 0, 0xfffff, GDT_FLAG_GRANUALRITY|GDT_FLAG_LONG, GDT_ACCESS_PRESENT|GDT_ACCESS_PRIV_RING0|GDT_ACCESS_TYPE|GDT_ACCESS_EXECUTABLE|GDT_ACCESS_READABLE_WRITABLE);
	set_GDT_entry8(&GDT[2], 0, 0xfffff, GDT_FLAG_GRANUALRITY|GDT_FLAG_LONG, GDT_ACCESS_PRESENT|GDT_ACCESS_PRIV_RING0|GDT_ACCESS_TYPE|GDT_ACCESS_READABLE_WRITABLE);
	set_GDT_entry16(((struct GDTDescr_16 *)&GDT[3]), (uint64_t)&TSS, sizeof(struct TSSSEGMENT)-1, GDT_FLAG_GRANUALRITY, GDT_ACCESS_PRESENT|GDT_ACCESS_PRIV_RING0|GDT_ACCESS_ACCESSED);

	tss_init(&TSS);
	gdt_address = (uint64_t)GDT ;
	gdt_ptrr[0] = (sizeof (struct GDTDescr_8) * 5 - 1) + ((gdt_address & 0xffffffffffff) << 16);
	gdt_ptrr[1] = (gdt_address >> 48) & 0xffff;
	
	__asm__ __volatile__ (
		"cli \t\n"
		"movq %0, %%rdx\t\n"
		"lgdt (%%rdx)\t\n"
		"movw $0x10, %%ax\t\n"
		"movw %%ax, %%ds\t\n"
		"movw %%ax, %%es\t\n"
		"movw %%ax, %%fs\t\n"
		"movw %%ax, %%gs\t\n"
		"movw %%ax, %%ss\t\n"
		"sti\t\n"
		"movw $0x18, %%di\t\n"
		"ltr %%di\t\n":
		:"a"(&gdt_ptrr));
}

void idt_init(void) {
	uint64_t irq_addresses[16];        
	uint64_t idt_address;
 
   //remapping the PIC 
	outb(0x20, 0x11); // start initialization sequence
    outb(0xA0, 0x11);
    outb(0x21, 0x20); // set vector offset
    outb(0xA1, 40);
    outb(0x21, 0x04); // tell master PIC that there is a slave PIC at IRQ2 (0100)
    outb(0xA1, 0x02); // tell slave PIC its cascade identity
    outb(0x21, 0x01); // tell 8086/88 mode (Gives additional information about environment)
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
	
	irq_addresses[0] = (uint64_t)irq0;
	irq_addresses[1] = (uint64_t)irq1;
	irq_addresses[2] = (uint64_t)irq2;
	irq_addresses[3] = (uint64_t)irq3;
	irq_addresses[4] = (uint64_t)irq4;
	irq_addresses[5] = (uint64_t)irq5;
	irq_addresses[6] = (uint64_t)irq6;
	irq_addresses[7] = (uint64_t)irq7;
	irq_addresses[8] = (uint64_t)irq8;
	irq_addresses[9] = (uint64_t)irq9;
	irq_addresses[10] = (uint64_t)irq10;
	irq_addresses[11] = (uint64_t)irq11;
	irq_addresses[12] = (uint64_t)irq12;
	irq_addresses[13] = (uint64_t)irq13;
	irq_addresses[14] = (uint64_t)irq14;
	irq_addresses[15] = (uint64_t)irq15;

	idt_address = (uint64_t)IDT ;
	idt_ptr[0] = (sizeof (struct IDTDescr) * 256 - 1) + ((idt_address & 0xffffffffffff) << 16);
	idt_ptr[1] = (idt_address >> 48) & 0xffff;

	set_IDT_entry(&IDT[3],(uint64_t)break_point, 0x08, 1, 0x8f); // set break_point handler
	set_IDT_entry(&IDT[8],(uint64_t)double_fault, 0x08, 1, 0x8e);


	for(int i=0; i<16; i++){
		set_IDT_entry(&IDT[32+i], irq_addresses[i], 0x08, 0, 0x8e);
	}
	
	__asm__ __volatile__ (
		"cli \t\n"
		"movq %0, %%rdx\t\n"
		"lidt (%%rdx)\t\n"
		"sti\t\n":
		:"a"(&idt_ptr));

	return;
}

void kernel_main(void) 
{
	/* Initialize terminal interface */
	gdt_init();
	idt_init();
	terminal_initialize();
	
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello Kernel");
	
	__asm__ __volatile__(
		"end_loop: hlt\t\n"
		"jmp end_loop"
		::
	);
}
