# $@ target file
# $< first dependency
# $^ all dependencies
#
C_SOURCES = $(wildcard kernel/*.c cpu/*.c lain/*.c)
HEADERS = $(wildcard kernel/*.h cpu/*.h lain/*.h)
OBJ_FILES = ${C_SOURCES:.c=.o cpu/interrupt.o}

all: run

kernel.bin: boot/kernel-entry.o ${OBJ_FILES} 
	x86_64-elf-ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

os-image.bin: boot/mbr.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-i386 -fda $<

%.o: %.c ${HEADERS}
	x86_64-elf-gcc -g -m32 -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	$(RM) */*.bin */*.o */*.dis

