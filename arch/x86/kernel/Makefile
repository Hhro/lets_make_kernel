TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -ffreestanding -Wall -Wextra -fexceptions -fno-rtti -fPIC

OBJS = cpuinfo.o flag.o

.PHONY: clean

all: ${OBJS}

%.o: %.cpp
	${CXX} -c $^ -o $@ -I ../include ${CXXFLAGS}

clean:
	rm -f ${OBJS}