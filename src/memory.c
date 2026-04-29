#include "memory.h"
#include <stdio.h>

/**
 * Custom memory management implementation.
 * Simulates virtual RAM with a global array and a free-list allocator.
 */

#define RAM_SIZE (1024 * 1024) // 1MB virtual RAM
static char ram[RAM_SIZE];

typedef struct MemoryBlock {
    int size;
    int is_free;
    struct MemoryBlock* next;
} MemoryBlock;

static MemoryBlock* head = (MemoryBlock*)ram;

void init_memory(void) {
    head->size = RAM_SIZE - sizeof(MemoryBlock);
    head->is_free = 1;
    head->next = 0;
}

void* alloc(int size) {
    MemoryBlock* curr = head;
    
    // Find first block that is free and has enough space
    while (curr) {
        if (curr->is_free && curr->size >= size) {
            // Split block if there's enough space for a new header and at least 1 byte
            if (curr->size >= (int)(size + sizeof(MemoryBlock) + 1)) {
                MemoryBlock* next_block = (MemoryBlock*)((char*)curr + sizeof(MemoryBlock) + size);
                next_block->size = curr->size - size - sizeof(MemoryBlock);
                next_block->is_free = 1;
                next_block->next = curr->next;
                
                curr->size = size;
                curr->next = next_block;
            }
            
            curr->is_free = 0;
            return (void*)((char*)curr + sizeof(MemoryBlock));
        }
        curr = curr->next;
    }
    
    return 0; // Allocation failed
}

void dealloc(void* ptr) {
    if (!ptr) return;
    
    MemoryBlock* block = (MemoryBlock*)((char*)ptr - sizeof(MemoryBlock));
    block->is_free = 1;
    
    // Simple coalescing: if the next block is also free, merge it
    MemoryBlock* curr = head;
    while (curr) {
        if (curr->is_free && curr->next && curr->next->is_free) {
            curr->size += sizeof(MemoryBlock) + curr->next->size;
            curr->next = curr->next->next;
            // Don't move to the next block yet, try merging further
        } else {
            curr = curr->next;
        }
    }
}
