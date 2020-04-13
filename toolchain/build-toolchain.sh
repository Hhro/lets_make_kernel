#!/bin/bash

# Setup variables
export PREFIX="$PWD/build/"
export PATH="$PREFIX/bin:$PATH"
export TARGET=x86_64-elf

function usage {
    printf "Usage: %s [toolchain] [clean]\n\n" $0
    echo "Arguments:"
    echo " toolchain     binutils, gcc (default=ALL)"
    echo " clean         clean-up build directory"
}

# Define build functions
function build_binutils {
    echo "Build binutils for $TARGET"
    mkdir "$PREFIX/binutils"
    cd "$PREFIX/binutils"
    ../../binutils-2.34/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make
    make install
}

function build_gcc {
    echo "Build gcc for $TARGET"
    # The $PREFIX/bin dir _must_ be in the PATH.
    which -- $TARGET-as || echo $TARGET-as is not in the PATH
    
    mkdir "$PREFIX/gcc"
    cd "$PREFIX/gcc"
    ../../gcc-9.3.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
}

# Define function for clean the build directory
function clean_up {
    echo "Clean-up build directory"
    rm -rf "$PREFIX/*"
}

# Designate target tools to build
if [ "$#" -eq 0 ]; then
    TARGET_TOOL=ALL
elif [ "$#" -eq 1 ]; then
    TARGET_TOOL=$1
else
    usage
    exit
fi

# Make root build directory
if [ ! -d "$PREFIX" ]; then
    mkdir "$PREFIX"
fi

# Build toolchains
case $TARGET_TOOL in
    "ALL")
        build_binutils
        build_gcc
        ;;
    "binutils")
        build_binutils
        ;;
    "gcc")
        build_gcc
        ;;
    "clean")
        clean_up
        ;;
    *)
        usage
        exit
esac
