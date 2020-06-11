#include <kapi/io.hpp>
#include <test.hpp>

#define QEMU_ISA_DEBUG_EXIT_PORT 0xF4

enum QEMUExitCode {
    Success = 0x10,
    Error = 0x11
};

void report_error() {
    outb(QEMU_ISA_DEBUG_EXIT_PORT, Error);
}

void report_success() {
    outb(QEMU_ISA_DEBUG_EXIT_PORT, Success);
}