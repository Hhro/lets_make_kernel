#include <stdint.h>
#include "./gdt.h"
#include "../asm/load.h"

static GDTENTRY8 init_gdt[4];
static GDTR init_gdtr = { sizeof(init_gdt) - 1 , (uint64_t )init_gdt };
static TSSSEGMENT init_tss;

void set_gdt_entry_8(GDTENTRY8 * entry, uint64_t base, uint32_t limit, uint8_t upperflag, uint8_t lowerflag, uint8_t type) {
    entry->wLowerLimit = limit & 0xFFFF;
    entry->wLowerBaseAddress = base & 0xFFFF;
    entry->bUpperBaseAddress1 = (base >> 16) & 0xFF;
    entry->bTypeAndLowerFlag = lowerflag | type;
    entry->bUpperLimitAndUpperFlag = ((limit >> 16) & 0xFF) | upperflag;
    entry->bUpperBaseAddress2 = (base >> 24) & 0xFF;
}

void set_gdt_entry_16(GDTENTRY16 * entry, uint64_t base, uint32_t limit, uint8_t upperflag, uint8_t lowerflag, uint8_t type) {
    entry->wLowerLimit = limit & 0xFFFF;
    entry->wLowerBaseAddress = base & 0xFFFF;
    entry->bMiddleBaseAddress1 = (base >> 16) & 0xFF;
    entry->bTypeAndLowerFlag = lowerflag | type;
    entry->bUpperLimitAndUpperFlag = ((limit >> 16) & 0xFF) | upperflag;
    entry->bMiddleBaseAddress2 = (base >> 24) & 0xFF;
    entry->dwUpperBaseAddress = base >> 32;
    entry->dwReserved = 0;
}

void initialize_gdt_tss( void ) {
    set_gdt_entry_8(&init_gdt[0], 0, 0, 0, 0, 0);
    set_gdt_entry_8(&init_gdt[1], 0, 0xFFFF, GDT_FLAGS_UPPER_CODE,
        GDT_FLAGS_LOWER_KERNELCODE, GDT_TYPE_CODE);
    set_gdt_entry_16((GDTENTRY16 *) &init_gdt[2], (uint64_t) &init_tss, sizeof(init_tss) - 1, GDT_FLAGS_UPPER_TSS,
        GDT_FLAGS_LOWER_TSS, GDT_TYPE_TSS);

    // TODO: implement memset
    for (int i = 0; i < sizeof(TSSSEGMENT); i++) {
        ((uint8_t *)&init_tss)[i] = 0;
    }
    init_tss.qwIST[0] = 0x800000;
    init_tss.wIOMapBaseAddress = 0xFFFF;
    load_gdtr(&init_gdtr);
    load_tr(0x10);
}