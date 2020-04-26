TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

OBJS = io.o

.PHONY: clean

all: ${OBJS}

io.o: io.S
	${CXX} -c ${CXXFLAGS} $^ -o $@

clean:
	rm -f $(OBJS)