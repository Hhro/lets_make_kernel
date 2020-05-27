#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <vga.h>

#include <common.hpp>
#include <error.hpp>
#include <kapi/cpuinfo.hpp>
#include <keyboard.hpp>
#include <stdio.hpp>

extern "C" void kernel_main(void);
extern KeyboardDevice DKeyboard;

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

    // Activate keyboard
    DKeyboard.Activate();

    /* Newline support is left as an exercise. */
    while (1) {
        uint8_t ch;
        ch = terminal_getchar();
        terminal_putchar(ch);
    }

    __asm__ __volatile__(
        "end_loop: hlt\t\n"
        "jmp end_loop" ::);
}
