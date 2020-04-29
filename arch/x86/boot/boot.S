#include <kapi/cr.hpp>
#include <kapi/gdt.hpp>
#include <kapi/msr.hpp>
#include <kapi/mmu.hpp>
#include <kapi/flag.hpp>

#include "multiboot2.h"

#define X86_FEATURE_LM_AVAIL	(1 << 29)

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
.comm low_pdpt, PDPT_SIZE, PDPT_ALIGN
.comm high_pdpt, PDPT_SIZE, PDPT_ALIGN
.comm low_page_directory_table, PD_SIZE, PD_ALIGN
.comm high_page_directory_table, PD_SIZE, PD_ALIGN


/*
	Multiboot2 standard does not set the stack pointer register
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

	/* check if processor supports long mode */
	call is_64_arch_avail
	jz error	//this kernel is only for processor supporting x86_64

	/* To transit to IA32-e mode, we need to prepare page table and GDT */
	call setup_page_tables
	call enable_paging

	lgdt gdt_ptr

	/* Transit to IA32-e mode */
	ljmp $GDT_ENTRY_SIZE, $_start64

	cli
	hlt
1:
	jmp 1b

is_cpuid_avail:
	// Check cpuid instruction is supported by attempting to 
	// Flip the ID bit of EFLAGS. If we can flip it, cpuid is available

	// Set %eax value as eflags
	pushfl
	pop %eax

	// Copy it to %ecx for comparaing after flipping
	mov %eax, %ecx

	// Flip the ID bit
	xor $(EFLAGS_ID), %eax
	
	// Copy %eax to eflags
	push %eax
	popfl

	// Set %eax value as eflags to compare with origin(%ecx)
	pushfl
	pop %eax

	// Restore original eflags because we flipped them.
	push %ecx
	popfl

	// Compare eax and ecx. If they are same, it means we can't flip ID bit.
	// Thus we can't use cpuid.
	// Return:
	//	%eax = 0 => no cpuid
	//	%eax = 1 => cpuid available
	xor %eax, %ecx
	ret

is_64_arch_avail:
	// Check Intel 64 architecture is supported by inspecting a result of the cpuid instruction

	// CPUID must be available
	call is_cpuid_avail
	jz .no_longmode
	
	// If maximum CPUID input value is below 0x80000001, we can't determine it supports 64 architecture or not.
	mov $0x80000000, %eax	// return maximum input value of ex-cpuid on %eax
	cpuid
	cmp $0x80000001, %eax
	jb .no_longmode
	
	// Get ex-cpuid information
	// If 29th bit of %edx is set, Intel 64bit architecture is supported
	mov $0x80000001, %eax
	cpuid
	and $(X86_FEATURE_LM_AVAIL), %edx
	jz .no_longmode

	xor %eax,%eax
	inc %eax

	ret

.no_longmode:
	xor %eax, %eax
	ret

setup_page_tables:
	/* 
		Setup 4-level-paging with page of 2MiB zize
		Because we're in booting proecdure, we use identity-mapping for ease
	*/

	/* Initialize PML4 */
	movl $low_pdpt, %eax
    or $(PML4E_PRESENT | PML4E_WRITABLE), %eax
    movl %eax, pml4 + (PML4_ADDR_TO_ENTRY_IDX(KERNEL_PHYSICAL_START) * PML4_ENTRY_SIZE)

    movl $high_pdpt, %eax
    or $(PML4E_PRESENT | PML4E_WRITABLE), %eax
    movl %eax, pml4 + (PML4_ADDR_TO_ENTRY_IDX(KERNEL_VIRTUAL_START) * PML4_ENTRY_SIZE)

	/* Initialize PDPT */
    movl $low_page_directory_table, %eax
    or $(PDPTE_PRESENT | PDPTE_WRITABLE), %eax
    movl %eax, low_pdpt + (PDPT_ADDR_TO_ENTRY_IDX(KERNEL_PHYSICAL_START) * PDPT_ENTRY_SIZE)

    movl $high_page_directory_table, %eax
    or $(PDPTE_PRESENT | PDPTE_WRITABLE), %eax
    movl %eax, high_pdpt + (PDPT_ADDR_TO_ENTRY_IDX(KERNEL_VIRTUAL_START) * PDPT_ENTRY_SIZE)

    mov $0, %ecx

    movl $_kernel_physical_end, %esi
    shrl $TWO_MEGABYTES_SHIFT, %esi
    addl $1, %esi
	
	/*movl $0x200, %esi*/

	/* Iterate to setup PD */
.page_directory_table_loop:
    movl $TWO_MEGABYTES, %eax
    mul %ecx
    or $(PDE_PRESENT | PDE_WRITABLE | PDE_HUGE), %eax
    movl %eax, low_page_directory_table(, %ecx, PD_ENTRY_SIZE)
    movl %eax, high_page_directory_table(, %ecx, PD_ENTRY_SIZE)

    inc %ecx
    cmp %esi, %ecx
    jne .page_directory_table_loop  // if not equal redo loop

	ret

enable_paging:
	/* CR3 is register pointer addressing PML4 */
	mov $pml4, %eax
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
	or $(KERNEL_CR0), %eax
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

1:	hlt
	jmp 1b
