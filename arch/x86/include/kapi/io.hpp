#ifndef KAPI_X86_IO_HPP
#define KAPI_X86_IO_HPP

#include <stdint.h>

static inline void outb(uint16_t port, uint8_t v) {
    __asm__ __volatile__("outb %0,%1" : : "a"(v), "dN"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

#endif
