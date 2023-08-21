
#include <stdio.h>
#include <stdlib.h>

#include "memory/counters.h" //i was to implement using block counters but i run out of time
#include "memory/freelist.h" //i was to implement freeing mechanism but i run out of time

#include <assert.h>
#include <string.h>

#define MEMORY_SIZE 1024 // Total size of memory in bytes

// Structure to represent a memory block
typedef struct Block
{
    size_t size;
    struct Block *next;
    int is_free;
} Block;

// The starting address of the memory pool
void *memory_pool;

// Function to initialize the memory pool
void initialize_memory_pool()
{
    memory_pool = malloc(MEMORY_SIZE);
    if (!memory_pool)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    Block *initial_block = (Block *)memory_pool;
    initial_block->size = MEMORY_SIZE - sizeof(Block);
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

// Function to free memory
void my_free(void *ptr)
{
    if (!ptr)
    {
        return;
    }
    Block *curr_block = (Block *)((char *)ptr - sizeof(Block));
    curr_block->is_free = 1;
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

int main()
{
    initialize_memory_pool();

    void *ptr1 = my_malloc(100);
    void *ptr2 = my_malloc(200);
    void *ptr3 = my_malloc(300);

    display_memory();

    my_free(ptr2);

    display_memory();

    my_free(ptr1);
    my_free(ptr3);

    display_memory();

    free(memory_pool);

    return 0;
}
