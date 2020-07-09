#ifndef TASK_H
#define TASK_H

#include <stdint.h>
#include <kapi/context.hpp>
#include <uapi/string.hpp>

class TaskControlBlock {
protected:
    Context context;

    uint64_t id;
    uint64_t flags;

    void *stack_address;
    uint64_t stack_size;
public:
    TaskControlBlock(uint64_t id, uint64_t flags, void *entrypoint, void *stack_address, uint64_t stack_size);
    Context *get_contextptr() {
        return &(this->context);
    }
};

extern "C" void switch_context(Context *current_context, Context *next_context);

#endif // TASK_H