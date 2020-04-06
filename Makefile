NAME = fried

# Now it only supports x86 architecture
KTARGET = i686-elf
ARCH = x86

TOOLCHAIN = toolchain/build/bin
AS = ${TOOLCHAIN}/${KTARGET}-as
CXX = ${TOOLCHAIN}/${KTARGET}-g++

QEMU = qemu-system-i386
QEMU_FLAGS += -curses # For remote development

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

###### Build kernel
build-kernel: 
	${MAKE} -C kernel KTARGET=${KTARGET}

ARCH_DIR = arch/${ARCH}
build-arch:
	${MAKE} -C ${ARCH_DIR}

install: clean build-kernel build-arch
	${CXX} -T ${ARCH_DIR}/boot/linker.ld -o ${NAME}.bin -ffreestanding -O2 -nostdlib ${ARCH_DIR}/boot/boot.o kernel/kernel.o -lgcc

###### Clean-up
clean:
	@for d in $(DIRS); \
	do \
		$(MAKE) -C $$d clean; \
	done

	rm -rf ${CLEAN_OBJ} ${CLEAN_DIR}