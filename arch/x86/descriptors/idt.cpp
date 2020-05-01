#include <stdint.h>
#include "../asm/load.h"
#include "./gdt.h"
#include "../../../include/terminal.h"

static IDTR init_idtr;
static IDTENTRY init_idt[100];


void set_idt_entry(IDTENTRY *entry, void *handler, uint16_t selector,
    uint8_t ist, uint8_t flags, uint8_t type) {
    entry->wLowerBaseAddress = (uint64_t) handler & 0xFFFF;
    entry->wSegmentSelector = selector;
    entry->bIST = ist & 0x3;
    entry->bTypeAndFlags = type | flags;
    entry->wMiddleBaseAddress = ((uint64_t) handler >> 16) & 0xFFFF;
    entry->dwUpperBaseAddress = ((uint64_t) handler >> 32);
    entry->dwReserved = 0;
}

void dummy_handler(void) {
    terminal_writestring("[!] THIS IS dummy handler\n");
}

void initialize_idt_tables(void) {
    init_idtr.qwBaseAddress = (uint64_t) init_idt;
    init_idtr.wLimit = 100 * sizeof(IDTENTRY) - 1;

    for(int i = 0; i < 100; i++) {
        set_idt_entry(&init_idt[i], (void *) dummy_handler, 0x08, 
            IDT_FLAGS_IST1, IDT_FLAGS_KERNEL, IDT_TYPE_INTERRUPT);
    }
    load_idtr(&init_idtr);
}

