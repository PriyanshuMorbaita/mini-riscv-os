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

    /* Define heap start and end */
    . = ALIGN(16);
    PROVIDE(heap_start = .);                 /* Heap starts after .bss */

    . = ORIGIN(RAM) + LENGTH(RAM) - 16K;     /* Reserve 16KB for stack */
    PROVIDE(heap_end = .);                   /* Heap ends before stack */

    PROVIDE(stack_top = .);                  /* Stack pointer initialized here */
}
