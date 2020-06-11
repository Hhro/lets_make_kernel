#! /bin/bash

if [ "$#" -lt 1 ]; then
    echo "$# is Illegal number of parameters."
    echo "Usage: $0 [options]"
	exit 1
fi

args=("$@")
echo "${args[0]}"
qemu-system-x86_64 -cpu Broadwell -cdrom "${args[0]}" -nographic -device isa-debug-exit,iobase=0xf4,iosize=0x01
status=$?
if [ "${status}" -eq 33 ]; then
    exit 0
fi
exit 1