#include "../main.h"

#define PGSIZE 4096
#define PGROUNDUP(sz) (((sz)+PGSIZE-1) & (PGSIZE-1))

void freerange(void *start,void *end);

extern char heap_start[];
extern char heap_end[];

struct run{
    struct run *next;
};

struct {
    struct spinlock lock;
    struct run *freelist;
}kmem;

void kinit(){
    initlock(&kmem.lock,"kmem");
    freerange(heap_start,heap_end);
}

void freerange(void *start, void *end){
    char *p;
    p = (char*)PGROUNDUP((uint64)start);
    for(; p+PGSIZE <= (char*)end; p += PGSIZE){
        kfree(p);
    }
}

void kfree(void *pa){
    struct run *r;

    if(((uint64)pa % PGSIZE) != 0 || (char*)pa < heap_start || (char*)heap_end){
        panic("kfree");
    }

    memset(pa,1,PGSIZE);

    r = (struct run*)pa;

    acquire(&kmem.lock);
    r->next = kmem.freelist;
    kmem.freelist = r;
    release(&kmem.lock);
}

void *kalloc(){
    struct run *r;

    acquire(&kmem.lock);
    r = kmem.freelist;
    if(r)
        kmem.freelist = r->next;
    release(&kmem.lock);

    if(r)
        memset((char*)r,5,PGSIZE);
    return (void*)r;
}