#include <kapi/const.hpp>
#include <kapi/flag.hpp>

// See if flag of EFLAGS is changable
bool IsFlagChangable(const u64 flag) {
    u64 f1, f2;

    asm volatile(
        "pushf\n"
        "pushf\n"
        "pop %0\n"
        "mov %0, %1\n"
        "xor %2, %0\n"
        "push %0\n"
        "popf\n"
        "pushf\n"
        "pop %0\n"
        "popf\n"
        : "=&r" (f1), "=&r" (f2)
        : "ir" (flag)
    );

    return ((f1^f2) & flag) != 0;
}
