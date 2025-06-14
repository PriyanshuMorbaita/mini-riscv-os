#ifndef SPINLOCK_H
#define SPINLOCK_H

typedef struct spinlock{
    unsigned int locked;
    char *name;
}spinlock;

void initlock(struct spinlock*, char*);
int acquire(struct spinlock*);
int release(struct spinlock*);
int holding(struct spinlock*);

#endif