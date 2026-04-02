#ifndef MEMORY_H
#define MEMORY_H

/**
 * Custom memory management library.
 * Simulates virtual RAM using a global array.
 */

/* Initialize the memory manager */
void init_memory(void);

/* Allocate a block of memory of given size (in bytes) */
void* alloc(int size);

/* Deallocate a previously allocated block of memory */
void dealloc(void* ptr);

#endif /* MEMORY_H */
