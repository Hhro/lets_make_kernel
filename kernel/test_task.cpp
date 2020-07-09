#include <stdint.h>
#include <fried/stdio.h>
#include <task.hpp>

// Maybe replaced to dynamic allocation of memory afterwards. 
static uint64_t test_task_stack[ 1024 ] = { 0, };

void test_task() {
    while (1) {
        puts("Test task working...");
    }
}

void start_test_task(char *buf) {
    TaskControlBlock task1(1, 0, (void *) test_task, (void *) test_task_stack, sizeof(test_task_stack));
    TaskControlBlock task0(0, 0, NULL, NULL, sizeof(test_task_stack));

    puts("Switching context...");
    switch_context(0, task1.get_contextptr());
}