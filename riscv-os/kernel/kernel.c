#include "../main.h"

void kernel_main(void) {
    volatile char *uart = (char *)0x10000000; 
    *uart = 'K'; 
    puts("Kernel has started...\n");

    puts("Before memory_init()");
    memory_init();
    puts("After memory_init()");

    puts("Before io_init()");
    io_init();
    puts("After io_init()");

    puts("Before multitask_init()");
    multitask_init();
    puts("After multitask_init()");
    puts("RISC-V Simple OS Kernel\n");
    puts("Initializing...\n");
    puts("Before shell_init()");
    shell_init();
    puts("After shell_init()");


    puts("Before shell_run()");
    shell_run();
    puts("After shell_run()");
    puts("Kernel halted\n");
    while(1) {
        asm volatile("wfi");
    }
}