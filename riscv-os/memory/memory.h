#ifndef MEMORY_H
#define MEMORY_H

#include "../include/types.h"

void memory_init(void);
void* malloc(size_t size);
void free(void *ptr);

#endif