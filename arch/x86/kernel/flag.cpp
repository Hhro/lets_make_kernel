#include <kapi/const.hpp>
#include <kapi/flag.hpp>

// See if flag of EFLAGS is changable
bool IsFlagChangable(const u32 flag) {
    u32 f1, f2;

    asm volatile(
        "pushfl\n"
        "pushfl\n"
        "popl %0\n"
        "movl %0, %1\n"
        "xorl %2, %0\n"
        "push %0\n"
        "popfl\n"
        "popl %0"
        "popfl\n"
        : "=&r" (f1), "=&r" (f2)
        : "ir" (flag)
    );

    return ((f1^f2) & flag) != 0;
}
