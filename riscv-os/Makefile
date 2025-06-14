CROSS_COMPILE = riscv64-unknown-elf-
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy
READELF = $(CROSS_COMPILE)readelf

# Architecture flags
ARCH_FLAGS = -march=rv32imac -mabi=ilp32
CFLAGS = $(ARCH_FLAGS) -nostdlib -ffreestanding -O2 -Wall -I. -Iio -Ikernel -Iuser
ASFLAGS = $(ARCH_FLAGS)
LDFLAGS = -melf32lriscv -T kernel/linker.ld

# Source files
BOOT_SRCS = kernel/bootloader.asm
C_SRCS = \
    io/io.c \
    kernel/kalloc.c \
    kernel/kernel.c \
    kernel/multitask.c \
    kernel/spinlock.c \
    user/memory.c \
    user/shell.c

ASM_SRCS = kernel/swtch.S

# Object files
BOOT_OBJS = $(BOOT_SRCS:.asm=.o)
C_OBJS = $(C_SRCS:.c=.o)
ASM_OBJS = $(ASM_SRCS:.S=.o)
OBJS = $(BOOT_OBJS) $(C_OBJS) $(ASM_OBJS)

# Output files
ELF = riscv-os.elf
BIN = riscv-os.bin

.PHONY: all clean run check_elf check_linker

all: check_linker $(BIN)

check_linker:
	@if [ ! -f kernel/linker.ld ]; then \
		echo "Error: linker.ld missing!"; exit 1; fi

$(BIN): $(ELF)
	$(OBJCOPY) -O binary -j .text -j .rodata -j .data $< $@

$(ELF): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AS) $(ASFLAGS) -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(ELF) $(BIN)

check_elf:
	@for file in $(OBJS); do \
		echo "Checking $$file:"; \
		$(READELF) -h $$file | grep 'Class\|Machine'; \
	done

run: all
	qemu-system-riscv32 -nographic -machine virt -bios none -kernel $(BIN)
