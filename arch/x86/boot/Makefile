TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fPIC

OBJS = boot.o

.PHONY: clean

all: ${OBJS}

%.o: %.S
	${CXX} -c $^ -o $@ -I ../include ${CXXFLAGS}

clean:
	rm -f $(OBJS)