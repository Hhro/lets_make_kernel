#include <stdint.h>
#include <fried/stdio.h>
#include <task.hpp>
#include <test.hpp>

static uint64_t test_task_stack[ 1024 ] = { 0, };

static void test_task () {
    report_success();
}

void test_main() {
    TaskControlBlock task(1, 0, (void *) test_task, (void *) test_task_stack, sizeof(test_task_stack));
    switch_context(0, task.get_contextptr());
    report_error();
}