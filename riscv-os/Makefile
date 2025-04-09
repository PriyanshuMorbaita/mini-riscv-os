CROSS_COMPILE = riscv64-unknown-elf-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
READELF = $(CROSS_COMPILE)readelf

SRC_DIR = .
BOOT_DIR = bootloader
KERNEL_DIR = kernel
MEM_DIR = memory
MULTI_DIR = multitasking
SHELL_DIR = shell
INCLUDE_DIR = include

ARCH_FLAGS = -march=rv32imac -mabi=ilp32
CFLAGS = $(ARCH_FLAGS) -nostdlib -ffreestanding -O2 -Wall -I.
ASFLAGS = $(ARCH_FLAGS)
LDFLAGS = -melf32lriscv -T $(KERNEL_DIR)/linker.ld

BOOT_SRCS = $(BOOT_DIR)/bootloader.asm
C_SRCS = $(KERNEL_DIR)/kernel.c \
         $(MEM_DIR)/memory.c \
         $(MULTI_DIR)/multitask.c \
         $(SHELL_DIR)/shell.c \
         $(INCLUDE_DIR)/io.c

BOOT_OBJS = $(BOOT_SRCS:.asm=.o)
C_OBJS = $(C_SRCS:.c=.o)
OBJS = $(BOOT_OBJS) $(C_OBJS)

ELF = riscv-os.elf
BIN = riscv-os.bin

.PHONY: all clean check_elf run

all: check_linker $(BIN)

check_linker:
	@if [ ! -f $(KERNEL_DIR)/linker.ld ]; then echo "Error: linker.ld missing!"; exit 1; fi

$(BIN): $(ELF)
	$(OBJCOPY) -O binary -j .text -j .rodata -j .data $< $@

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

clean:
	rm -f $(OBJS) $(ELF) $(BIN)

check_elf:
	@for file in $(OBJS); do \
		echo "Checking $$file:"; \
		$(READELF) -h $$file | grep 'Class\|Machine'; \
	done

run: all
	qemu-system-riscv32 -nographic -machine virt -bios none -kernel $(BIN)
