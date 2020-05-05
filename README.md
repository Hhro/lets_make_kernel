# Let's develop kernel

This is my repository for kernel developing project of CyKor.

Target architecture is x86_64

# Build

```bash
make install
```

# Run with QEMU

This kernel could be run on QEMU, use this command:

```bash
make run-iso
```

# Build with cmake

```bash
mkdir build
cd build
CC=../toolchain/build/bin/x86_64-elf-gcc CXX=../toolchain/build/bin/x86_64-elf-g++ cmake ..
make
```