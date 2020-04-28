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
 
irq0:
  call irq0_handler
  iret
 
irq1:
  call irq1_handler
  iret
 
irq2:
  call irq2_handler
  iret
 
irq3:
  call irq3_handler
  iret
 
irq4:
  call irq4_handler
  iret
 
irq5:
  call irq5_handler
  iret
 
irq6:
  call irq6_handler
  iret
 
irq7:
  call irq7_handler
  iret
 
irq8:
  call irq8_handler
  iret
 
irq9:
  call irq9_handler
  iret
 
irq10:
  call irq10_handler
  iret
 
irq11:
  call irq11_handler
  iret
 
irq12:
  call irq12_handler
  iret
 
irq13:
  call irq13_handler
  iret
 
irq14:
  call irq14_handler
  iret
 
irq15:
  call irq15_handler
  iret
 