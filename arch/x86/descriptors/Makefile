TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

OBJS = gdt.o idt.o

.PHONY: clean

all: ${OBJS}

gdt.o: gdt.cpp
	${CXX} -c ${CXXFLAGS} $^ -o $@

idt.o: idt.cpp
	${CXX} -c ${CXXFLAGS} $^ -o $@

clean:
	rm -f $(OBJS)