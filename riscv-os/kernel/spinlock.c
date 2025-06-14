#include "spinlock.h"

void initlock(struct spinlock *lk, char *name){
    lk->locked = 0;
    lk->name = name;
}

int acquire(struct spinlock* lk){
    if(holding(lk)){
        return -1;
    }    

    while(__sync_lock_test_and_set(&lk->locked,1) != 0);

    __sync_synchronize();

    return 0; 
}

int release(struct spinlock *lk){
    if(!holding(lk)){
        return -1;
    }

    __sync_lock_release(&lk->locked);

    return 0;
}


int holding(struct spinlock *lk){
    int r;
    r = (lk->locked);
    return r;
}