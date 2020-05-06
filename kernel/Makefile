TOOLCHAIN = ../toolchain/build/bin
KTARGET = x86_64-elf
ARCH = x86

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti

OBJS = kernel.o

.PHONY: clean

all: kernel.o

ARCH_DIR = ../arch/${ARCH}
kernel.o: 
	${CXX} -c kernel.cpp -o $@ ${CXXFLAGS} -I ../include -I ${ARCH_DIR}/include

clean:
	rm -f $(OBJS)