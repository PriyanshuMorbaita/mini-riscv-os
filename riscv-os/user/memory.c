#include "../main.h"

#define HEAP_START 0x80200000
#define HEAP_SIZE  0x200000 

typedef struct block {
    size_t size;
    bool free;
    struct block *next;
} block_t;

static block_t *head = NULL;

void memory_init(void) {
    head = (block_t*)HEAP_START;
    head->size = HEAP_SIZE - sizeof(block_t);
    head->free = true;
    head->next = NULL;

    puts("Memory system initialized\n");
}

void* malloc(size_t size) {
    block_t *curr = head;

    size = (size + 7) & ~7;

    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->size > size + sizeof(block_t) + 8) {
                block_t *new_block = (block_t*)((char*)curr + sizeof(block_t) + size);
                new_block->size = curr->size - size - sizeof(block_t);
                new_block->free = true;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }

            curr->free = false;
            return (void*)((char*)curr + sizeof(block_t));
        }

        curr = curr->next;
    }

    return NULL;
}

void free(void *ptr) {
    if (!ptr) return;

    block_t *block = (block_t*)((char*)ptr - sizeof(block_t));
    block->free = true;

    if (block->next && block->next->free) {
        block->size += sizeof(block_t) + block->next->size;
        block->next = block->next->next;
    }
}



void memory_stats(memory_info_t *info) {
    block_t *curr = head;

    info->total = HEAP_SIZE;
    info->used = 0;
    info->free = 0;
    info->total_blocks = 0;
    info->used_blocks = 0;
    info->free_blocks = 0;

    while (curr) {
        info->total_blocks++;
        if (curr->free) {
            info->free += curr->size;
            info->free_blocks++;
        } else {
            info->used += curr->size;
            info->used_blocks++;
        }

        curr = curr->next;
    }
}


void memset(void *ptr, int value, size_t num) {
    unsigned char *p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
}
