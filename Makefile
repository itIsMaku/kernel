AS=nasm
CC = gcc-13
CFLAGS = -ffreestanding -O2 -Wall -Wextra -nostdlib -m32 -fno-builtin

OBJS= \
	kernel/boot.o \
	kernel/kernel.o \
	kernel/lib/string.o \
	kernel/lib/memory.o \
	kernel/lib/stdio.o \
	kernel/drivers/vga.o \
	kernel/drivers/keyboard.o \
	kernel/shell/shell.o \
	kernel/shell/shutdown.o

all: iso/volkmanos.iso

kernel/boot.o:
	$(AS) -f elf32 kernel/boot.asm -o kernel/boot.o

kernel/kernel.o:
	$(CC) $(CFLAGS) -c kernel/kernel.c -o kernel/kernel.o

kernel/lib/string.o:
	$(CC) $(CFLAGS) -c kernel/lib/string.c -o kernel/lib/string.o

kernel/lib/memory.o:
	$(CC) $(CFLAGS) -c kernel/lib/memory.c -o kernel/lib/memory.o

kernel/lib/stdio.o:
	$(CC) $(CFLAGS) -c kernel/lib/stdio.c -o kernel/lib/stdio.o

kernel/drivers/vga.o:
	$(CC) $(CFLAGS) -c kernel/drivers/vga.c -o kernel/drivers/vga.o

kernel/drivers/keyboard.o:
	$(CC) $(CFLAGS) -c kernel/drivers/keyboard.c -o kernel/drivers/keyboard.o

kernel/shell/shell.o:
	$(CC) $(CFLAGS) -c kernel/shell/shell.c -o kernel/shell/shell.o

kernel/shell/shutdown.o:
	$(CC) $(CFLAGS) -c kernel/shell/shutdown.c -o kernel/shell/shutdown.o

iso/boot/kernel.bin: $(OBJS)
	$(CC) $(CFLAGS) -T kernel/linker.ld $(OBJS) -o iso/boot/kernel.bin

iso/volkmanos.iso: iso/boot/kernel.bin
	grub-mkrescue -o iso/volkmanos.iso iso

clean:
	rm -f kernel/**/*.o kernel/*.o iso/boot/kernel.bin iso/volkmanos.iso
