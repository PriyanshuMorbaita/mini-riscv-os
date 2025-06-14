#ifndef MULTITASK_H
#define MULTITASK_H

#include "types.h"

#define NPROC 16
#define STACK_SIZE 4096

typedef void (*task_func_t)(void);

struct proc* create_proc(task_func_t, const char*);
void multitask_init(void);
void destroy_proc(struct proc*);
void schedular(void);
void swtch(struct context*, struct context*);
int allocpid();
void start_process(void);
struct proc *myproc();
void testmulti(void);

#endif 