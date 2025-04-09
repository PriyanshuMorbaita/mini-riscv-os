OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
    RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS
{
    . = ORIGIN(RAM);

    .text : {
        *(.text.init)
        *(.text .text.*)
    } > RAM

    .rodata : {
        *(.rodata .rodata.*)
    } > RAM

    .data : {
        *(.data .data.*)
    } > RAM

    .bss (NOLOAD) : {
        _bss_start = .;
        *(.bss .bss.* COMMON)
        _bss_end = .;
    } > RAM

    . = ALIGN(4K);
    . = ORIGIN(RAM) + LENGTH(RAM) - 16K;
    stack_top = .;
}
