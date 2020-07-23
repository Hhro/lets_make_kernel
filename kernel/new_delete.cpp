#include <new>
#include <buddy_alloc.hpp>

void operator delete(void *p) { BAllocator.free(p); }
void operator delete[](void *p) { BAllocator.free(p); }

void operator delete(void *p, std::size_t n) { BAllocator.free(p); }
void operator delete[](void *p, std::size_t n) { BAllocator.free(p); }

void *operator new(std::size_t n) { return BAllocator.malloc(n); }
void *operator new[](std::size_t n) { return BAllocator.malloc(n); }
