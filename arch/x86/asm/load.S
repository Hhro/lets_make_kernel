#define ASM_FILE        1

.intel_syntax noprefix

.section .text
.global load_gdtr, load_tr, load_idtr
.type load_gdtr, @function
.type load_tr, @function
.type load_idtr, @function


load_gdtr:
    lgdt [ rdi ]
    ret

load_tr:
    ltr di
    ret

load_idtr:
    lidt [ rdi ]
    ret

