TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -ffreestanding -Wall -Wextra -fexceptions -fno-rtti -fPIC

OBJS = cpuinfo.o flag.o idt.o irq_asm.o

.PHONY: clean

all: ${OBJS}

%.o: %.cpp
	${CXX} -c $^ -o $@ -I ../include -I ../../../kernel/include ${CXXFLAGS}

clean:
	rm -f ${OBJS}