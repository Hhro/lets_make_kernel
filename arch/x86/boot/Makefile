TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -z max-page-size=0x1000 --ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fPIC -mcmodel=kernel -mno-red-zone  -Wa,--divide -g

OBJS = boot.o

.PHONY: clean

all: ${OBJS}

%.o: %.S
	${CXX} -c $^ -o $@ -I ../include ${CXXFLAGS}

clean:
	rm -f $(OBJS)