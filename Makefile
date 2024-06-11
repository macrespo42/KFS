CFLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -ffreestanding -O2 -Wall -Wextra -std=gnu99

LDFLAGS = -ffreestanding -O2 -nostdlib

CC = i686-elf-gcc

NAME = kfs.iso

all: $(NAME)

$(NAME):
	i686-elf-as boot.s -o boot.o
	i686-elf-as gdt.s -o gdts.o
	i686-elf-gcc -c kernel.c -o kernel.o $(CFLAGS)
	i686-elf-gcc -c gdt.c -o gdt.o $(CFLAGS)
	i686-elf-gcc -T linker.ld -o kfs.bin $(LDFLAGS) boot.o kernel.o gdt.o gdts.o  -lgcc
	mv kfs.bin isodir/boot/kfs.bin
	grub-mkrescue -o $(NAME) isodir


install:
	qemu-system-i386 -cdrom $(NAME)


clean:
	rm -rf boot.o kernel.o


fclean: clean
	rm -rf isodir/boot/kfs.bin
	rm -rf kfs.iso


cross-compiler:
	./dev-tools/cross-compiler-deps.sh	


check:
	./dev-tools/multiboot_check.sh

re: fclean all

.PHONY: clean fclean re install cross-compiler check
