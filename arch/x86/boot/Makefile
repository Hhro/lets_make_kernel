TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = i686-elf

AS = ${TOOLCHAIN}/${KTARGET}-as
CXXFLAGS = --ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

OBJS = boot.o

.PHONY: clean

all: boot.o

boot.o:
	${AS} boot.s -o $@

clean:
	rm -f $(OBJS)