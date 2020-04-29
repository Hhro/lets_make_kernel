TOOLCHAIN = ../toolchain/build/bin
KTARGET = x86_64-elf
ARCH = x86

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -z max-page-size=0x1000 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -mcmodel=kernel -mno-red-zone -g -mno-mmx -mno-sse -mno-sse2

AS = ${TOOLCHAIN}/${KTARGET}-as
OBJS =  kernel.o IRQ/idt.o IRQ/irq_asm.o

.PHONY: clean

#all:  kernel.o IRQ/idt.o IRQ/irq_asm.o
all: kernel.o IRQ/idt.o IRQ/irq_asm.o

ARCH_DIR = ../arch/${ARCH}
kernel.o: 
	${CXX} -c kernel.cpp -o $@ ${CXXFLAGS} -I ../include -I ${ARCH_DIR}/include

IRQ/idt.o:
	${CXX} -c IRQ/idt.cpp  -o $@ ${CXXFLAGS}

IRQ/irq_asm.o:
	${CXX} -c IRQ/irq_asm.S -o ${@} -mcmodel=kernel

clean:
	rm -f $(OBJS)