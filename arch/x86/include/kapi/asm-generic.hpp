#ifndef KAPI_X86_ASM_GENERIC_HPP
#define KAPI_X86_ASM_GENERIC_HPP

/* Inline assembly macros */

// Many traditional Intel instructions like rdmsr return value in form of
// EDX:EAX where EDX stands for high value and EAX for low.
// These macros can help you avoid some tedious inline assembly jobs required
// to handle those instructions.
#define DECLARE_ARGS(low, high) unsigned long low, high
#define EAX_EDX_VAL(low, high) ((low) | (high) << 32)
#define EAX_EDX_RET(low, high) "=a"(low), "=d"(high)

#endif  // KAPI_X86_ASM_GENERIC_HPP
