#include <arch/common.hpp>
#include <kapi/gdt.hpp>
#include <kapi/idt.hpp>

bool arch_init() {
    gdt_init();
    idt_init();

    return true;
}