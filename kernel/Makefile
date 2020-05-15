TOOLCHAIN = ../toolchain/build/bin
KTARGET = x86_64-elf
ARCH = x86

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -z max-page-size=0x1000 -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -mcmodel=kernel -mno-red-zone -g -mno-mmx -mno-sse -mno-sse2

AS = ${TOOLCHAIN}/${KTARGET}-as
OBJS =  kernel.o

.PHONY: clean

all: kernel.o 

ARCH_DIR = ../arch/${ARCH}
kernel.o: 
	${CXX} -c kernel.cpp  -o $@ ${CXXFLAGS} -I ../arch/x86/include

clean:
	rm -f $(OBJS)