#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <vga.h>

#include <common.hpp>
#include <error.hpp>
#include <kapi/cpuinfo.hpp>

extern "C" void kernel_main(void);

void kernel_main(void) {
    arch_init();
    terminal_initialize();

    // Collect CPU information
    cpu_info = CpuInfo();
    cpu_info.CollectCpuInfo();

    if (cpu_info.IsIntel()) {
        terminal_writestring("Powered by ");
        terminal_writestring(cpu_info.cpu_vendor_id());
    }

    while (1) {
    }

    // unreachable code
    unreachable_error();
}
