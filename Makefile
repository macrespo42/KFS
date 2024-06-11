CFLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -ffreestanding -O2 -g -std=gnu99

CFLAGS:=$(CFLAGS) -Wall -Wextra

LDFLAGS = -ffreestanding -O2 -nostdlib

CC = i686-elf-gcc

BOOTDIR = sysroot/boot

NAME = kfs.iso

all: $(NAME)

$(NAME):
	i686-elf-as boot.s -o boot.o
	i686-elf-gcc -c kernel.c -o kernel.o $(CFLAGS)
	i686-elf-gcc -T linker.ld -o kfs.bin $(LDFLAGS) boot.o kernel.o -lgcc
	mv kfs.bin $(BOOTDIR)/kfs.bin
	grub-mkrescue -o $(BOOTDIR)/$(NAME) sysroot


install:
	qemu-system-i386 -cdrom $(BOOTDIR)/$(NAME)


clean:
	rm -rf boot.o kernel.o


fclean: clean
	rm -rf $(BOOTDIR)/kfs.bin
	rm -rf $(BOOTDIR)/kfs.iso


cross-compiler:
	./dev-tools/cross-compiler-deps.sh


check:
	./dev-tools/multiboot_check.sh

re: fclean all

.PHONY: clean fclean re install cross-compiler check
