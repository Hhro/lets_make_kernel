// include your own headers.
#include <test.hpp>
#include <buddy_alloc.hpp>
#include <fried/stdio.h>

extern BuddyAllocator BAllocator;

void test_main() {
    void * ptr;
    ptr = BAllocator.malloc(24);
    printf("addr : %x", ptr);
    *(uint32_t *)ptr = 0xdeadbeef;
    printf("content : %x\n", *(uint32_t *)ptr);

    if (!ptr) {
        report_error();
    }

    if(!BAllocator.free(ptr)) {
        report_error();
    }
    report_success();
}