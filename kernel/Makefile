TOOLCHAIN = ../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = -ffreestanding -Wall -Wextra -fno-exceptions -fno-rtti
INCLUDES = -I../include

OBJS = kernel.o keyboard/keyboard.o terminal.o

.PHONY: clean

all: ${OBJS}

kernel.o: 
	${CXX} -c ${INCLUDES} kernel.cpp -o $@ ${CXXFLAGS} 

terminal.o: 
	${CXX} -c ${INCLUDES} terminal.cpp -o $@ ${CXXFLAGS} 

keyboard/keyboard.o:
	${CXX} -c ${INCLUDES} keyboard/keyboard.cpp -o $@ ${CXXFLAGS} 

clean:
	rm -f $(OBJS)