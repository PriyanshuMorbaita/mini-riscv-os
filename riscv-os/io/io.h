#ifndef IO_H
#define IO_H

#include "../main.h"

void io_init(void);

void putchar(char c);
char getchar(void);
void puts(const char *s);
void gets(char *buffer, size_t size);
void printf(const char *fmt, ...);
void print_dec(size_t num);
void panic(const char*);
void strncpy(char *, const char *, size_t);
#endif 