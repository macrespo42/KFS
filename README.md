# KFS_1

## Grub boot, and screen

### Feature of the actual Kernel:

- A kernel you can boot via Grub
- An ASM bootable base
- Some basic code to prime some stuff on the screen
- A basic 'Hello world' kernel

### Requirements:

- A linux host machine with grub installed and apt (if you want install compiler dependencies with the makefile rule)
- quemu
- A [cross compiler](https://wiki.osdev.org/GCC_Cross-Compiler)
- Cross compiler dependencies: ``make cross-compiler`` to install it
- export env var present in dev-tools/export ``$(cat dev-tools/export)`` work for example

For the cross-compiler, We using: [i686-elf-gcc (GCC) 13.3.1](https://ftp.gnu.org/gnu/gcc/gcc-13.3.0/gcc-13.3.0.tar.xz) and [binutils-2.42](https://ftp.gnu.org/gnu/binutils/binutils-2.42.tar.xz)

### How to use

We provide a Makefile with this project to facilitate the installation

- ``make`` compile the kernel and provie a kfs.iso
- ``make check`` verify if the kernel is bootable
- ``make cross-compiler`` install cross-compiler dependencies
- ``make install`` boot the kernel in quemu
- ``make clean`` delete obj files
- ``make fclean`` same as clean but delete bin and iso too
