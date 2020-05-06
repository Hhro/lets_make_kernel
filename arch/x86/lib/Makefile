TOOLCHAIN = ../../../toolchain/build/bin
KTARGET = x86_64-elf

CXX = ${TOOLCHAIN}/${KTARGET}-g++
CXXFLAGS = --ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -fPIC

OBJS = memcpy.o memset.o
LIB = libkernel.a

${LIB}: ${OBJS}
		${AR} rv $@ ${OBJS}

%.o: %.cpp
		$(CXX) -c -I ../include $< -o $@

clean:
	rm -f ${OBJS} ${LIB}