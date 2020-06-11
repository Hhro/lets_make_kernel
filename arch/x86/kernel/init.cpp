#include <common.hpp>
#include <kapi/gdt.hpp>
#include <kapi/idt.hpp>
#include <pit.hpp>

extern PITDevice DPIT;

bool arch_init() {
    gdt_init();
    idt_init();
    DPIT.init_IRQ0(8000);

    return true;
}