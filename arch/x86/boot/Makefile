TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = --ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fPIC

OBJS = boot.o

.PHONY: clean

all: ${OBJS}

boot.o: boot.S
	${CXX} -c $^ -o $@

clean:
	rm -f $(OBJS)