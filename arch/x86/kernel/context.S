.global switch_context
.extern switch_context

.macro macro_save_context
    push %rbp
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rdi
    push %rsi
    push %r8
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    mov %ds, %ax
    push %rax
    mov %es, %ax
    push %rax
    push %fs
    push %gs
.endm

.macro macro_load_context
    pop %gs
    pop %fs
    pop %rax
    mov %ax, %es
    pop %rax
    mov %ax, %ds

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rsi
    pop %rdi
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax
    pop %rbp
.endm

switch_context:
    push %rbp
    movq %rsp, %rbp

    pushfq
    cmp $0, %rdi
    je load_context
    popfq

    push %rax

    mov %ss, %ax
    movq %rax, (23 * 8)(%rdi)
    movq %rbp, %rax
    add $16, %rax
    movq (22 * 8)(%rdi), %rax

    pushfq
    pop %rax
    movq %rax, (21 * 8)(%rdi)

    mov %cs, %ax
    movq %rax, (20 * 8)(%rdi)

    movq 8(%rbp), %rax
    movq %rax, (19 * 8)(%rdi) 

    pop %rax
    pop %rbp

    add $(19 * 8), %rdi
    movq %rdi, %rsp
    sub $(19 * 8), %rdi

    macro_save_context

load_context:
    movq %rsi, %rsp
    macro_load_context
    iretq