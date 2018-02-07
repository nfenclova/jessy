symbol-file build/kernel.sym
target remote | qemu-system-x86_64 -S -gdb stdio -cdrom build/kernel.iso
break _start
