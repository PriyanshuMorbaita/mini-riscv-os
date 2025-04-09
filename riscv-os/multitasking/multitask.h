#ifndef MULTITASK_H
#define MULTITASK_H

#include "../include/types.h"

typedef void (*task_func_t)(void);

void multitask_init(void);
uint32_t create_task(task_func_t func);
void yield(void);
void schedule(void);
void task2(void);
void task1(void);
void run_all_tasks(void);
void multitask_test(void);

#endif 