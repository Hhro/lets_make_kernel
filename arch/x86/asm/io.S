#define ASM_FILE        1

.intel_syntax noprefix

.section .text
.global outport_byte, inport_byte
.type outport_byte, @function
.type inport_byte, @function

inport_byte:
    push rdx

    mov rdx, rdi
    mov rax, 0
    in al, dx

    pop rdx
    ret

outport_byte:
    push rdx
    push rax

    mov rdx, rdi
    mov rax, rsi
    out dx, al

    pop rax
    pop rdx

    ret