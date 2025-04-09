#include "../main.h"

#define MAX_TASKS 16
#define STACK_SIZE 4096

typedef struct {
    uint32_t regs[32];  
    uint32_t pc;        
    void *stack;        
    bool active;        
    task_func_t func;   
} task_t;

static task_t tasks[MAX_TASKS];
static uint32_t current_task = 0;
static uint32_t next_task_id = 0;



void multitask_init(void) {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].active = false;
    }
    puts("Multitasking system initialized\n");
}

uint32_t create_task(task_func_t func) {
    if (next_task_id >= MAX_TASKS) {
        return -1;
    }

    uint32_t id = next_task_id++;
    tasks[id].active = true;
    tasks[id].func = func;

    tasks[id].stack = malloc(STACK_SIZE);
    if (!tasks[id].stack) {
        tasks[id].active = false;
        next_task_id--;
        return -1;
    }

    tasks[id].pc = (uint32_t)func;
    tasks[id].regs[2] = (uint32_t)tasks[id].stack + STACK_SIZE;  // sp

    return id;
}

void schedule(void) {
    uint32_t next = (current_task + 1) % MAX_TASKS;

    while (next != current_task) {
        if (tasks[next].active) {
            current_task = next;
            return;
        }
        next = (next + 1) % MAX_TASKS;
    }
}

void yield(void) {
    schedule();
}



void task1(void) {
    for (int i = 0; i < 5; i++) {
        puts("Task 1 is running\n");
        yield();
    }
}

void task2(void) {
    for (int i = 0; i < 5; i++) {
        puts("Task 2 is running\n");
        yield();
    }
}

void run_all_tasks(void) {
    bool any_active;

    do {
        any_active = false;

        for (int i = 0; i < next_task_id; i++) {
            if (tasks[i].active) {
                current_task = i;
                tasks[i].func();
                any_active = true;
            }
        }

    } while (any_active);
}



void multitask_test(void) {
    multitask_init();

    if (create_task(task1) == -1) puts("Failed to create task1\n");
    if (create_task(task2) == -1) puts("Failed to create task2\n");

    run_all_tasks();
}
