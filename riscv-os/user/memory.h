#ifndef MEMORY_H
#define MEMORY_H

#include "../main.h"

void memory_init(void);
void* malloc(size_t size);
void free(void *ptr);
void memset(void*, int, size_t);

#endif