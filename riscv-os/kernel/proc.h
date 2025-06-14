#ifndef PROC_H
#define PROC_H

#include "spinlock.h"

struct context{
    uint64 ra;  
    uint64 sp;

    uint64 s0;
    uint64 s1;
    uint64 s2;
    uint64 s3;
    uint64 s4;
    uint64 s5;
    uint64 s6;
    uint64 s7;
    uint64 s8;
    uint64 s9;
    uint64 s10;
    uint64 s11;
};

enum procstate { USED, UNUSED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE};

typedef struct proc{
    struct spinlock lock;
    enum procstate state;
    int pid;

    task_func_t func;
    void *stack;
    struct context context;
    char name[16];
}proc;

#endif