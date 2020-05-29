#include <error.hpp>

[[noreturn]] void unreachable_error() {
    while (1) {
        asm volatile("hlt");
    }
}