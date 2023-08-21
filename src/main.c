#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "main.h"

// Structure to represent a memory block

typedef struct Block
{
    size_t size;
    struct Block *prev;
    struct Block *next;
    int is_free;
} Block;

Block *freeList = NULL; // Global pointer to the start of the heap
// The starting address of the memory pool
void *memory_pool;

// Function to initialize the memory pool
void initialize_memory_pool(size_t MEM_SIZE)
{
    memory_pool = malloc(MEM_SIZE);
    if (!memory_pool)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    Block *initial_block = (Block *)memory_pool;
    initial_block->size = MEM_SIZE - sizeof(Block);
    initial_block->next = NULL;
    initial_block->is_free = 1;
}

// Function to allocate memory
void *my_malloc(size_t size)
{
    Block *curr_block = (Block *)memory_pool;
    while (curr_block)
    {
        if (curr_block->is_free && curr_block->size >= size)
        {
            if (curr_block->size > size + sizeof(Block))
            {
                Block *new_block = (Block *)((char *)curr_block + sizeof(Block) + size);
                new_block->size = curr_block->size - size - sizeof(Block);
                new_block->next = curr_block->next;
                new_block->is_free = 1;
                curr_block->size = size;
                curr_block->next = new_block;
            }
            curr_block->is_free = 0;
            return (char *)curr_block + sizeof(Block);
        }
        curr_block = curr_block->next;
    }
    return NULL; // Out of memory
}

void mergeWithNext(Block *block)
{
    if (block->next && block->next->is_free)
    {
        block->size += block->next->size + sizeof(Block);
        block->next = block->next->next;
        if (block->next)
        {
            block->next->prev = block;
        }
    }
}

// Function to merge a free block with its previous block
void mergeWithPrev(Block *block)
{
    if (block->prev && block->prev->is_free)
    {
        block->prev->size += block->size + sizeof(Block);
        block->prev->next = block->next;
        if (block->next)
        {
            block->next->prev = block->prev;
        }
        block = block->prev;
    }
}

// Function to free memory

// Function to free memory
void my_free(void *ptr)
{
    if (!ptr)
    {
        return; // Nothing to free
    }

    Block *block = (Block *)((char *)ptr - sizeof(Block));
    block->is_free = 1;

    mergeWithNext(block);
    mergeWithPrev(block);
}

// Function to display memory status
void display_memory()
{
    Block *curr_block = (Block *)memory_pool;
    printf("Memory Status:\n");
    while (curr_block)
    {
        printf("Block: %p, Size: %lu, Free: %d\n", curr_block, curr_block->size, curr_block->is_free);
        curr_block = curr_block->next;
    }
}
