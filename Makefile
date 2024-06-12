CFLAGS = -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs -ffreestanding -O2 -Wall -Wextra -std=gnu99 -I includes/

LDFLAGS = -ffreestanding -O2 -nostdlib

CC = i686-elf-gcc

KERNEL_SRC = kernel tty libk

NAME = kfs.iso

SRC = $(addsuffix .c, $(addprefix src/, $(KERNEL_SRC)))

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	i686-elf-as boot.s -o boot.o
	$(CC) -T linker.ld -o kfs.bin $(LDFLAGS) boot.o $(OBJ) -lgcc
	mv kfs.bin isodir/boot/kfs.bin
	grub-mkrescue -o $(NAME) isodir

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

install:
	qemu-system-i386 -cdrom $(NAME)

clean:
	rm -rf boot.o $(OBJ)

fclean: clean
	rm -rf isodir/boot/kfs.bin
	rm -rf kfs.iso

cross-compiler:
	./dev-tools/cross-compiler-deps.sh	

check:
	./dev-tools/multiboot_check.sh

re: fclean all

.PHONY: clean fclean re install cross-compiler check
