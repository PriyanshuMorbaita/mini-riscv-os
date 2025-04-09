make -f Makefile clean && make -f Makefile

qemu-system-riscv32 \
    -machine virt \
    -cpu rv32 \
    -m 128M \
    -nographic \
    -bios none \
    -kernel riscv-os.bin

if [ "$1" == "debug" ]; then
    qemu-system-riscv32 \
        -machine virt \
        -cpu rv32 \
        -m 128M \
        -nographic \
        -bios none \
        -kernel riscv-os.bin \
        -gdb tcp::1234 -S \
        -serial mon:stdio
fi