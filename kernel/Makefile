TOOLCHAIN = ../toolchain/build/bin
KTARGET = i686-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

OBJS = kernel.o

.PHONY: clean

all: kernel.o

kernel.o: 
	${CXX} -c kernel.cpp -o $@ ${CXXFLAGS} 

clean:
	rm -f $(OBJS)