// include your own headers.
#include <test.hpp>
#include <buddy_alloc.hpp>
#include <fried/stdio.h>

extern BuddyAllocator BAllocator;

void test_malloc_free() {
    void * ptr;
    ptr = BAllocator.malloc(24);
    printf("addr : %x\n", ptr);
    *(uint32_t *)ptr = 0xdeadbeef;
    printf("content : %x\n", *(uint32_t *)ptr);

    if (!ptr) {
        report_error();
    }

    if(!BAllocator.free(ptr)) {
        report_error();
    }
}

void test_new_delete() {
    int * ptr = new int;
    printf("addr : %x\n", ptr);
    *ptr = 0xdeadbeef;
    printf("content : %x\n", *(uint32_t *)ptr);
    assert_test(ptr != NULL);
    assert_test(*ptr == 0xdeadbeef);
    delete ptr;
}

void test_main() {
    test_malloc_free();
    test_new_delete();
    report_success();
}