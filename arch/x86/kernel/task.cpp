#include <stdint.h>
#include <task.hpp>
#include <kapi/context.hpp>
#include <uapi/string.hpp>


TaskControlBlock::TaskControlBlock(uint64_t id, uint64_t flags, void *entrypoint, void *stack_address, uint64_t stack_size) {
    // Initialize context
    memset(&this->context, 0, sizeof(this->context));

    this->context.rsp = (uint64_t) stack_address + stack_size;
    this->context.rbp = (uint64_t) stack_address + stack_size;

    // Set segment selector
    this->context.cs = 0x08;
    this->context.ds = 0x10;
    this->context.es = 0x10;
    this->context.fs = 0x10;
    this->context.gs = 0x10;
    this->context.ss = 0x10;

    // rip register
    this->context.rip = (uint64_t) entrypoint;

    // Interrupt enable
    this->context.rflags |= 0x0200;

    this->id = id;
    this->flags = flags;
    this->stack_address = stack_address;
    this->stack_size = stack_size;
}

