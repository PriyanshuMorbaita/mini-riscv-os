#ifndef SHELL_H
#define SHELL_H

#include "../main.h"

typedef int (*cmd_func_t)(int argc, char **argv);

void shell_init(void);
void shell_run(void);

int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
size_t strlen(const char *s);

#endif 