#include "multiboot2.h"
#include "cr.h"
#include "gdt.h"
#include "msr.h"
#include "kernel.h"
#include "mmu.h"

.set MB_HEADER_LEN, multiboot_header_end - multiboot_header
.set MB_CHECKSUM, -(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT2_ARCHITECTURE_I386 + MB_HEADER_LEN)

.set STACK_SIZE, 0x1000
.set STACK_ALIGNMENT, 8

.section .multiboot
multiboot_header:
	.long MULTIBOOT2_HEADER_MAGIC
	.long MULTIBOOT2_ARCHITECTURE_I386
	.long MB_HEADER_LEN
	.long MB_CHECKSUM

	/* multiboot tags go here */
	.short	MULTIBOOT_HEADER_TAG_END
	.short	0
	.long	8
	/* multiboot tags end here */
multiboot_header_end:

.section .bss
/* setup page tables for 2MiB, 4-level-paging */
.comm pml4, PML4_SIZE, PML4_ALIGN
.comm pdpt, PDPT_SIZE, PDPT_ALIGN
.comm pd, PD_SIZE, PD_ALIGN

/*
	Multiboot2 standard does not define the stack pointer register
	and it is up to kernel to provide a stack. This allocates
	small room for a small stack by creating a symbol at bss.
*/
stack_bottom:
.comm stack, STACK_SIZE, STACK_ALIGNMENT
stack_top:

.section .rodata
/* setup gdt */
.align GDT_TABLE_ALIGNMENT
gdt:
	.8byte	GDT_NULL_ENTRY
	.8byte	GDT_KERNEL_CODE
gdt_end:
	.skip (GDT_TABLE_SIZE - (gdt_end-gdt))
gdt_ptr:
	.short GDT_TABLE_SIZE-1
	.long gdt

.code32
.section .text
.global _start
.type _start, @function
_start:
	/* now we have a stack */
	movl $stack_top, %esp

	call setup_page_tables
	call enable_paging

	lgdt gdt_ptr

	ljmp $GDT_ENTRY_SIZE, $_start64

	hlt

setup_page_tables:
	movl $pdpt, %eax
	or $(PML4E_PRESENT | PML4E_WRITABLE), %eax
	movl %eax, pml4

	movl $pd, %eax
	or $(PDPTE_PRESENT | PDPTE_WRITABLE), %eax
	movl %eax, pdpt

	mov $0, %ecx

.map_pd_table:
	mov $0x200000, %eax
	mul %ecx
	or $(PDE_PRESENT | PDE_WRITABLE | PDE_HUGE), %eax
	mov %eax, pd(, %ecx, PD_ENTRY_SIZE)

	inc %ecx
	cmp $0x200, %ecx
	jne .map_pd_table

	ret

enable_paging:
	/* CR3 is register pointer addressing PML4 */
	mov pml4, %eax
	mov %eax, %cr3

	/* Enable page address extension */
	mov %cr4, %eax
	or $(CR4_PAE), %eax
	mov %eax, %cr4

	/* Enable long mode */
	mov $MSR_EFER, %ecx
	rdmsr
	or $(MSR_EFER_LME), %eax
	wrmsr

	/* Enable paging */
	mov %cr0, %eax
	or $(CR0_PG), %eax
	mov %eax, %cr0
	
	ret

error:
	movl $0xb8000, %eax
	movl $0x4f524f45, (%eax)
	movl $0x4f3a4f52, 4(%eax)
	movl $0x4f204f20, 8(%eax)
	movb %al, 0xb800a
	hlt

.code64
.global _start64
.type _start64, @function
_start64:
	mov $0, %ax
	mov %ss, %ax
	mov %ds, %ax
	mov %es, %ax
	mov %fs, %ax
	mov %gs, %ax

	call kernel_main

	hlt