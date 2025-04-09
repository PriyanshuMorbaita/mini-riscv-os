#ifndef MAIN_H
#define MAIN_H
 
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef int (*cmd_func_t)(int argc, char **argv);

typedef struct {
    size_t total;
    size_t used;
    size_t free;
    int total_blocks;
    int used_blocks;
    int free_blocks;
} memory_info_t;

void memory_stats(memory_info_t *info);

#include "uart.h"

 #include "include/io.h"
 #include "include/types.h"
 
 #include "memory/memory.h"
 
 #include "multitasking/multitask.h"
 
 #include "shell/shell.h"
 
 
 #endif 