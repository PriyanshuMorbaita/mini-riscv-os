#ifndef MAIN_H
#define MAIN_H
 
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdatomic.h>

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

#include "io/uart.h"

 #include "io/io.h"
 #include "kernel/types.h"
 
 #include "user/memory.h"
 
 #include "kernel/kalloc.h"
 #include "kernel/multitask.h"
 
 #include "user/shell.h"
 
 #include "kernel/spinlock.h"
 #include "kernel/proc.h"

 
 #endif 