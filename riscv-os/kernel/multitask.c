#include "../main.h"

int nextpid = 1;
struct spinlock pid_lock;
static proc procs[NPROC];
static struct proc *current_proc = NULL;
_Atomic int no_proc = {0};

void multitask_init(void) {
    initlock(&pid_lock,"nextpid");
    for (int i = 0; i < NPROC; i++) {
        initlock(&procs[i].lock,"proc");
        procs[i].state = UNUSED;
        procs[i].stack = NULL;
    }
    puts("Multitasking system initialized\n");
}

int allocpid(){
    acquire(&pid_lock);
    int pid = nextpid;
    nextpid = nextpid + 1;
    release(&pid_lock);
    return pid;
}

struct proc *myproc(){
    return current_proc;
}

void proc_start(void){
    if(current_proc && current_proc->func){
        current_proc->func();
    }

    acquire(&current_proc->lock);
    current_proc->state = ZOMBIE;
    release(&current_proc->lock);
}

struct proc* create_proc(task_func_t func, const char *name) {
    struct proc *p;

    for(p = procs; p < &procs[NPROC]; p++){
        acquire(&p->lock);
        if(p->state == UNUSED){
            p->pid = allocpid();
            p->state = USED;
            p->func = func;
            
            p->stack = kalloc(STACK_SIZE);
            if(!p->stack){
                release(&p->lock);
                return NULL;
            }
            memset(p->stack,0,STACK_SIZE);
            strncpy(p->name,name,sizeof(p->name)-1);
            p->state = RUNNABLE;
            atomic_fetch_add_explicit(&no_proc,1,memory_order_release);

            void *stack_top = (char *)p->stack + STACK_SIZE;

            memset(&p->context, 0, sizeof(p->context));
            p->context.sp = (uint32_t)stack_top;
            p->context.ra = (uint32_t) proc_start;

            release(&p->lock);
            printf("Created Task\n");
            return p;
        }else{
            release(&p->lock);
        }
    }
    return NULL;
}

void destroy_proc(struct proc *p){
    p->state = UNUSED;
    p->pid = 0;
    p->func = NULL;
    if(p->stack){
        kfree(p->stack);
        p->stack = NULL;
    }
    memset(&p->context, 0, sizeof(p->context));
    p->name[0] = 0;
}

void schedular(void){
    struct proc *p;
    for(;;){
        int found = 0;
        for(p = procs; p < &procs[NPROC]; p++){
            acquire(&p->lock);
            if(p->state == RUNNABLE){
                p->state = RUNNING;

                swtch(&current_proc->context,&p->context);
                current_proc = p;

                if(p->state == ZOMBIE){
                    destroy_proc(p);
                }

                current_proc = NULL;
                found = 1;
            }
            release(&p->lock);
        }
        if(found == 0){
            // while(atomic_load_explicit(&no_proc,memory_order_acquire) <= 0){
            //     printf("Waiting for the task\n");
            // }
            for(int i=0; i<1000000; i++);
            panic("Finished");
        }
    }
}

void test1(){
    for(int i=0; i<100; i++){
        printf("Priyanshu");
    }
}

void test2(){
    for(int i=0; i<100; i++){
        printf("Priyanshu");
    }
}

void test3(){
    for(int i=0; i<100; i++){
        printf("Morbaita");
    } 
}

void test4(){
     for(int i=0; i<100; i++){
        printf("Yadav");
    }
}
void test5(){
     for(int i=0; i<100; i++){
        printf("Chetona");
    }
}

void test6(){
     for(int i=0; i<100; i++){
        printf("Bera");
    }
}

void testmulti(void){
    create_proc(test1,"test1");
    create_proc(test2,"test2");
    create_proc(test3,"test3");
    create_proc(test4,"test4");
    create_proc(test5,"test5");
    create_proc(test6,"test6");
}