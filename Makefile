NAME = fried

# Now it only supports x86 architecture
KTARGET = x86_64-elf
ARCH = x86

TOOLCHAIN = toolchain/build/bin
CXX = ${TOOLCHAIN}/${KTARGET}-g++

QEMU = qemu-system-x86_64
QEMU_FLAGS = -curses\
			 -cpu Broadwell

DEBUG_FLAGS = -gdb tcp::${DEBUG_PORT}

CLEAN_OBJ = ${NAME}.bin ${NAME}.iso
CLEAN_DIR = isodir
DIRS = arch kernel

.PHONY: all install run-iso build-isodir mk-iso clean

###### Run with Qemu
build-isodir: install
	@mkdir -p isodir/boot/grub
	@cp ${NAME}.bin isodir/boot/${NAME}.bin
	@cp grub.cfg isodir/boot/grub/grub.cfg

mk-iso: build-isodir
	@grub-mkrescue -o fried.iso isodir

run-iso: mk-iso
	${QEMU} -cdrom ${NAME}.iso ${QEMU_FLAGS}

##### Debug with Qemu
debug: mk-iso
	${QEMU} -cdrom ${NAME}.iso ${QEMU_FLAGS} ${DEBUG_FLAGS}

###### Build kernel
build-kernel: 
	${MAKE} -C kernel KTARGET=${KTARGET}

ARCH_DIR = arch/${ARCH}
build-arch:
	${MAKE} -C ${ARCH_DIR}

OBJS = ${ARCH_DIR}/boot/boot.o kernel/kernel.o ${ARCH_DIR}/kernel/cpuinfo.o ${ARCH_DIR}/kernel/flag.o ${ARCH_DIR}/kernel/idt.o ${ARCH_DIR}/kernel/irq_asm.o
CXXFLAGS = -lkernel -lgcc -Wl,--build-id=none -ffreestanding -O2 -nostdlib
install: clean build-kernel build-arch
	#${CXX} -mcmodel=kernel -z max-page-size=0x1000 -T ${ARCH_DIR}/boot/linker.ld -o ${NAME}.bin -ffreestanding -O2 -nostdlib ${ARCH_DIR}/boot/boot.o kernel/kernel.o kernel/IRQ/idt.o kernel/IRQ/irq_asm.o -lgcc -Wl,--build-id=none
	#${CXX} -T ${ARCH_DIR}/boot/linker.ld -o ${NAME}.bin -ffreestanding -O2 -nostdlib ${ARCH_DIR}/boot/boot.o kernel/kernel.o kernel/IRQ/idt.o kernel/IRQ/irq_asm.o -g -lgcc -Wl,--build-id=none -mcmodel=kernel -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -z max-page-size=0x1000
	${CXX} -z max-page-size=0x1000 -T ${ARCH_DIR}/boot/linker.ld -o ${NAME}.bin ${OBJS} \
			-L ${ARCH_DIR}/lib ${CXXFLAGS}
###### Clean-up
clean:
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d clean; \
	done

	rm -rf ${CLEAN_OBJ} ${CLEAN_DIR}
