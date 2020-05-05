.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15
.global break_point
.global double_fault
 
 /*
.global irq0_handler
.global irq1_handler
.global irq2_handler
.global irq3_handler
.global irq4_handler
.global irq5_handler
.global irq6_handler
.global irq7_handler
.global irq8_handler
.global irq9_handler
.global irq10_handler
.global irq11_handler
.global irq12_handler
.global irq13_handler
.global irq14_handler
.global irq15_handler
.global bp_handler
*/
 
.extern irq0_handler
.extern irq1_handler
.extern irq2_handler
.extern irq3_handler
.extern irq4_handler
.extern irq5_handler
.extern irq6_handler
.extern irq7_handler
.extern irq8_handler
.extern irq9_handler
.extern irq10_handler
.extern irq11_handler
.extern irq12_handler
.extern irq13_handler
.extern irq14_handler
.extern irq15_handler
.extern double_fault_handler

.macro save_registers
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
.endm

.macro restore_registers
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
.endm

break_point:
  save_registers
  call bp_handler
  restore_registers
  iretq

double_fault:
  save_registers
  call double_fault_handler
  restore_registers
  add $0x8, %rsp
  iretq

irq0:
  save_registers
  call irq0_handler
  restore_registers
  iretq
 
irq1:
  save_registers
  call irq1_handler
  restore_registers
  iretq
 
irq2:
  save_registers
  call irq2_handler
  restore_registers
  iretq
 
irq3:
  save_registers
  call irq3_handler
  iretq
 
irq4:
  save_registers
  call irq4_handler
  restore_registers
  iretq
 
irq5:
  save_registers
  call irq5_handler
  restore_registers
  iretq
 
irq6:
  save_registers
  call irq6_handler
  restore_registers
  iretq
 
irq7:
  save_registers
  call irq7_handler
  restore_registers
  iretq
 
irq8:
  save_registers
  call irq8_handler
  restore_registers
  iretq
 
irq9:
  save_registers
  call irq9_handler
  restore_registers
  iretq
 
irq10:
  save_registers
  call irq10_handler
  restore_registers
  iretq
 
irq11:
  save_registers
  call irq11_handler
  restore_registers
  iretq
 
irq12:
  save_registers
  call irq12_handler
  restore_registers
  iretq
 
irq13:
  save_registers
  call irq13_handler
  restore_registers
  iretq
 
irq14:
  save_registers
  call irq14_handler
  restore_registers
  iretq
 
irq15:
  save_registers
  call irq15_handler
  restore_registers
  iretq
 