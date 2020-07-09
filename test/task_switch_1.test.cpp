#include <stdint.h>
#include <task.hpp>
#include <test.hpp>

static uint64_t test_task_stack[ 1024 ] = { 0, };

static void test_task () {
    report_success();
}

void test_main() {
    TaskControlBlock task1(1, 0, (void *) test_task, (void *) test_task_stack, sizeof(test_task_stack));
    TaskControlBlock task0(0, 0, (void *) 0, 0, sizeof(test_task_stack));
    switch_context(task0.get_contextptr(), task1.get_contextptr());
    report_error();
}